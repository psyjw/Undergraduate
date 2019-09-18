#include <stdlib.h>
#include <sys/time.h>
#include "coursework.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t empty;							//semaphore used to control the producer
sem_t full;								//semaphore used to control the consumer
sem_t sync;								//semaphore used to prevent multiple threads entering the critical section
sem_t mutex;							//semaphore used to prevent multiple consumers going asleep before the producer quits
sem_t mutexResponse;					//semaphore used to prevent multiple consmuers modifying total response time
sem_t mutexTurnAround;					//semaphore used to prevent multiple consmuers modifying total turn around time
struct process *head = NULL;			//Pointer to the head of the list, which stores all processes
struct process *tail = NULL;			//Pointer to the tail of the list, which stores all processes
int totalResponse=0;					//used for calculating average response time
int totalTurnAround=0;					//used for calculating average turn around time
int counter=NUMBER_OF_PROCESSES;		//used for recording number of consumed processes
int runTime[NUMBER_OF_PROCESSES]={0};	//used for recording each process has run for how many times

//function used to generate new processes and insert them into the list
void addprocess(struct process *newprocess) {
	//add the process to the Ready Queue
	newprocess->iState = READY;
	//if there is no process in the list
	if (head==NULL) {
		head = newprocess;
		tail = newprocess;
		head->oNext = NULL;
	}
	else {
		tail->oNext = newprocess;		//add the process to the end of the list
		tail = tail->oNext;				//let the 'tail' pointer points to the end of the list
		tail->oNext = NULL;
	}
}

//consumer thread
void * consumer(void *h) {
	int consumerId=*((int*)h);		//record current consumer's ID
	
	struct timeval start;			//stores time when the process starts to run
	struct timeval end;				//stores time when the process is finished
	int responseDiff = 0;			//stores the response time of the process
	int turnAroundDiff = 0;			//stores the turn around time of the process
	int preBurstTime;				//stores the process's burst time before its running
	struct process *temp;			//pointer points to the current process which needs to run
	
	while (1) {	
		sem_wait(&mutex);			//we assume during every loop, a process is consumed and finished (to decrease the value of counter by 1), in order to:
		counter = counter-1;		//prevent multiple consumer threads from being slept by semaphore 'full'
		if (counter < 0) {			//because when producer cannot produce processes any more, semaphore 'full' cannot increase
			counter = counter+1;	//thus these sleeping consumer cannot be waken up
			sem_post(&mutex);		//so we need to finish these consumers before they enter semaphore 'full' to prevent deadlock
			return;
		}
		sem_post(&mutex);

		sem_wait(&full);
		sem_wait(&sync);
		
		temp=head;
		//if there is only one process in the list
		if (head == tail) {
			head=head->oNext;
			tail = head;
		}
		else {
			head = head->oNext;
		}
		
		sem_post(&sync);
		//since we do not know whether the process has finished, we should not post 'empty' here in order to spare a space for the current process if it is not finished
		
		runTime[temp->iProcessId]=runTime[temp->iProcessId]+1;
		preBurstTime = temp->iBurstTime;
		simulateRoundRobinProcess(temp, &start, &end);
		turnAroundDiff = getDifferenceInMilliSeconds(temp->oTimeCreated, end);
		responseDiff = getDifferenceInMilliSeconds(temp->oTimeCreated, start);

		//when a process is the first time to run and its burst time is more than the time slice
		if ((runTime[temp->iProcessId]==1)&&(temp->iState == READY)) {
			sem_wait(&mutex);
			counter=counter+1;		//since the process is not finished during this loop, we should calculate the value of 'counter' back
			sem_post(&mutex);

			printf("Consumer Id = %d, Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Response Time = %d\n", consumerId, temp->iProcessId, preBurstTime, temp->iBurstTime, responseDiff);

			sem_wait(&mutexResponse);
			totalResponse = totalResponse + responseDiff;
			sem_post(&mutexResponse);
			
			sem_wait(&sync);	
			addprocess(temp);		//the process is not finished, add it back to the list
			sem_post(&sync);		
			sem_post(&full);		//we need to post 'full' here to let consumers know a new process (the one which is not finished) is added to the list
		}
		//when a process is the first time to run and its burst time is less than the time slice
		else if ((runTime[temp->iProcessId]==1)&&(temp->iState == FINISHED)){
			printf("Consumer Id = %d, Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Response Time = %d, Turn Around Time = %d\n", consumerId, temp->iProcessId, preBurstTime, temp->iBurstTime, responseDiff, turnAroundDiff);
			
			sem_wait(&mutexResponse);
			totalResponse = totalResponse + responseDiff;
			sem_post(&mutexResponse);
			sem_wait(&mutexTurnAround);
			totalTurnAround = totalTurnAround + turnAroundDiff;
			sem_post(&mutexTurnAround);

			free(temp);				//the process is finished, free the allocated memory
			sem_post(&empty);		//the process is finished, we can now post 'empty' to let producer generate a new process to add into the list
		}
		//when a process is not the first time to run and its remaining burst time is more than the time slice
		else if ((runTime[temp->iProcessId]!=1)&&(temp->iState == READY)) {
			sem_wait(&mutex);
			counter=counter+1;		//since the process is not finished during this loop, we should calculate the value of 'counter' back
			sem_post(&mutex);

			printf("Consumer Id = %d, Process Id = %d, Previous Burst Time = %d, New Burst Time = %d\n", consumerId, temp->iProcessId, preBurstTime, temp->iBurstTime);

			sem_wait(&sync);	
			addprocess(temp);		//the process is not finished, add it back to the list
			sem_post(&sync);	
			sem_post(&full);		//we need to post 'full' here to let consumers know a new process (the one which is not finished) is added to the list	
		}
		//when a process is not the first time to run and its remaining burst time is less than the time slice
		else if ((runTime[temp->iProcessId]!=1)&&(temp->iState == FINISHED)) {
			printf("Consumer Id = %d, Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Turn Around Time = %d\n", consumerId, temp->iProcessId, preBurstTime, temp->iBurstTime, turnAroundDiff);

			sem_wait(&mutexTurnAround);
			totalTurnAround = totalTurnAround + turnAroundDiff;
			sem_post(&mutexTurnAround);

			free(temp);				//the process is finished, free the allocated memory
			sem_post(&empty);		//the process is finished, we can now post 'empty' to let producer generate a new process to add into the list
		}
	}
}

//producer thread
void * producer(void *h) {
	int c=0;
	while (c < NUMBER_OF_PROCESSES) {
		struct process *newprocess = generateProcess();

		sem_wait(&empty);	
		sem_wait(&sync);		
		addprocess(newprocess);
		sem_post(&sync);	
		sem_post(&full);

		c=c+1;	
	}
}

int main() {	
	int i,j;
	int consumerId[NUMBER_OF_CONSUMERS];

	sem_init(&sync,0,1);				//initialize semaphore
	sem_init(&mutexResponse,0,1);		//initialize semaphore
	sem_init(&mutexTurnAround,0,1);		//initialize semaphore
	sem_init(&mutex,0,1);				//initialize semaphore
	sem_init(&full,0,0);				//initialize semaphore
	sem_init(&empty,0, BUFFER_SIZE);	//initialize semaphore to the size of the buffer
	
	pthread_t tid[NUMBER_OF_CONSUMERS+1];
	for (i=0; i<NUMBER_OF_CONSUMERS; i++) {
		consumerId[i]=i+1;
		pthread_create(&tid[i+1], NULL, consumer, (void *)(&consumerId[i]));
	}
	pthread_create(&tid[0], NULL, producer,  NULL);
	for (j=0; j<=NUMBER_OF_CONSUMERS; j++) {
		pthread_join(tid[j], NULL);
	}

	double aveResponse = (double)totalResponse/NUMBER_OF_PROCESSES;
	double aveTurnAround = (double)totalTurnAround/NUMBER_OF_PROCESSES;
	printf("Average Response Time = %f\n", aveResponse);
	printf("Average Turn Around Time = %f\n", aveTurnAround);
}