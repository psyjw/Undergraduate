#include <stdlib.h>
#include <sys/time.h>
#include "coursework.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t empty;											//semaphore used to control the producer
sem_t full;												//semaphore used to control the consumer
sem_t sync;												//semaphore used to prevent multiple threads entering the Ready Queue
sem_t mutex;											//semaphore used to prevent multiple consumers going asleep before the producer quits
sem_t syncmutex[NUMBER_OF_EVENT_TYPES];					//semaphore used to prevent multiple threads entering Event Queues
sem_t mutexResponse;									//semaphore used to prevent multiple consmuers modifying total response time
sem_t mutexTurnAround;									//semaphore used to prevent multiple consmuers modifying total turn around time
struct process *head = NULL;							//Pointer to the head of the list, which stores all processes
struct process *tail = NULL;							//Pointer to the tail of the list, which stores all processes
struct process *eventHead[NUMBER_OF_EVENT_TYPES];		//Pointer array to the head of different event queues (index is the type of event queue)
struct process *eventTail[NUMBER_OF_EVENT_TYPES];		//Pointer array to the tail of different event queues (index is the type of event queue)
int totalResponse=0;									//used for calculating average response time
int totalTurnAround=0;									//used for calculating average turn around time
int counter=NUMBER_OF_PROCESSES;						//used for recording number of consumed processes
int runTime[NUMBER_OF_PROCESSES]={0};					//used for recording each process has run for how many times
int Consumer=NUMBER_OF_CONSUMERS;						//used for recording number of quitted consumers (for eventmanager to decide when to quit)

//function used to generate new processes and insert them into the list
void addprocess(struct process *newprocess, struct process **start, struct process **end) {
	//if there is no process in the list
	if (*start==NULL) {
		*start = newprocess;
		*end = newprocess;
		(*start)->oNext = NULL;
	}
	else {
		(*end)->oNext = newprocess;		//add the process to the end of the list
		*end = (*end)->oNext;			//let the 'tail' pointer points to the end of the list
		(*end)->oNext = NULL;
	}
}

//consumer thread
void * consumer(void *h) {
	int consumerId=*((int*)h);			//record current consumer's ID
	
	struct timeval start;				//stores time when the process starts to run
	struct timeval end;					//stores time when the process is finished
	int responseDiff = 0;				//stores the response time of the process
	int turnAroundDiff = 0;				//stores the turn around time of the process
	int preBurstTime;					//stores the process's burst time before its running
	struct process *temp;				//pointer points to the current process which needs to run
	
	while (1) {
		sem_wait(&mutex);				//we assume during every loop, a process is consumed and finished (to decrease value of the counter by 1), in order to:
		counter = counter-1;			//prevent multiple consumer threads from being slept by semaphore 'full'
		if (counter < 0) {				//because when producer cannot produce processes any more, semaphore 'full' cannot increase
			counter = counter+1;		//thus these sleeping consumer cannot be waken up
			Consumer = Consumer-1;		//so we need to finish these consumers before they enter semaphore 'full' to prevent deadlock
			sem_post(&mutex);			
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
		simulateBlockingRoundRobinProcess(temp, &start, &end);
		turnAroundDiff = getDifferenceInMilliSeconds(temp->oTimeCreated, end);
		responseDiff = getDifferenceInMilliSeconds(temp->oTimeCreated, start);

		if ((runTime[temp->iProcessId]==1)&&(temp->iState == BLOCKED)) {
			sem_wait(&mutex);
			counter=counter+1;		//since the process is not finished during this loop, we should calculate the value of 'counter' back
			sem_post(&mutex);

			printf("Consumer Id = %d, Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Response Time = %d\nProcess %d blocked on event type %d\n", consumerId, temp->iProcessId, preBurstTime, temp->iBurstTime, responseDiff, temp->iProcessId, temp->iEventType);
			
			sem_wait(&mutexResponse);
			totalResponse = totalResponse + responseDiff;
			sem_post(&mutexResponse);

			sem_wait(&syncmutex[temp->iEventType]);
			addprocess(temp, &eventHead[temp->iEventType], &eventTail[temp->iEventType]);		//the process is blocked, add it to the corresponding event queue
			sem_post(&syncmutex[temp->iEventType]);
		}
		else if ((runTime[temp->iProcessId]!=1)&&(temp->iState == BLOCKED)) {
			sem_wait(&mutex);
			counter=counter+1;		//since the process is not finished during this loop, we should calculate the value of 'counter' back
			sem_post(&mutex);

			printf("Consumer Id = %d, Process Id = %d, Previous Burst Time = %d, New Burst Time = %d\nProcess %d blocked on event type %d\n", consumerId, temp->iProcessId, preBurstTime, temp->iBurstTime, temp->iProcessId, temp->iEventType);
			
			sem_wait(&syncmutex[temp->iEventType]);
			addprocess(temp, &eventHead[temp->iEventType], &eventTail[temp->iEventType]);		//the process is blocked, add it to the corresponding event queue
			sem_post(&syncmutex[temp->iEventType]);
		}
		//when a process is the first time to run and its burst time is more than the time slice
		else if ((runTime[temp->iProcessId]==1)&&(temp->iState == READY)) {
			sem_wait(&mutex);
			counter=counter+1;		//since the process is not finished during this loop, we should calculate the value of 'counter' back
			sem_post(&mutex);

			printf("Consumer Id = %d, Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Response Time = %d\n", consumerId, temp->iProcessId, preBurstTime, temp->iBurstTime, responseDiff);
			
			sem_wait(&mutexResponse);
			totalResponse = totalResponse + responseDiff;
			sem_post(&mutexResponse);
		
			sem_wait(&sync);	
			addprocess(temp, &head, &tail);		//the process is not finished, add it back to the list
			sem_post(&sync);	
			sem_post(&full);					//we need to post 'full' here to let consumers know a new process (the one which is not finished) is added to the list
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

			free(temp);							//the process is finished, free the allocated memory
			sem_post(&empty);					//the process is finished, we can now post 'empty' to let producer generate a new process to add into the list
		}
		//when a process is not the first time to run and its remaining burst time is more than the time slice
		else if ((runTime[temp->iProcessId]!=1)&&(temp->iState == READY)) {
			sem_wait(&mutex);
			counter=counter+1;		//since the process is not finished during this loop, we should calculate the value of 'counter' back
			sem_post(&mutex);

			printf("Consumer Id = %d, Process Id = %d, Previous Burst Time = %d, New Burst Time = %d\n", consumerId, temp->iProcessId, preBurstTime, temp->iBurstTime);
			
			sem_wait(&sync);	
			addprocess(temp, &head, &tail);		//the process is not finished, add it back to the list
			sem_post(&sync);	
			sem_post(&full);					//we need to post 'full' here to let consumers know a new process (the one which is not finished) is added to the list
		}
		//when a process is not the first time to run and its remaining burst time is less than the time slice
		else if ((runTime[temp->iProcessId]!=1)&&(temp->iState == FINISHED)) {
			printf("Consumer Id = %d, Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Turn Around Time = %d\n", consumerId, temp->iProcessId, preBurstTime, temp->iBurstTime, turnAroundDiff);
			
			sem_wait(&mutexTurnAround);
			totalTurnAround = totalTurnAround + turnAroundDiff;
			sem_post(&mutexTurnAround);

			free(temp);							//the process is finished, free the allocated memory
			sem_post(&empty);					//the process is finished, we can now post 'empty' to let producer generate a new process to add into the list
		}
	}
}

//producer thread
void * producer(void *h) {
	int c=0;
	while (c < NUMBER_OF_PROCESSES) {
		struct process *newprocess = generateProcess();
		//add the process to the Ready Queue
		newprocess->iState = READY;

		sem_wait(&empty);	
		sem_wait(&sync);	
		addprocess(newprocess, &head, &tail);	
		sem_post(&sync);	
		sem_post(&full);	

		c=c+1;
	}
}

//eventmanager thread
void * eventmanager(void *h) {
	struct process *temp;
	int i;
	while (1) {
		if (Consumer == 0) {					//when all consumer threads have quitted, quit the eventmanager thread
			return;
		}
		usleep(20000);								//eventmanager thread checks event queues for every 20ms
		for (i=0; i<NUMBER_OF_EVENT_TYPES; i++) {
			//if there are processes in event queues
			if (eventHead[i]!=NULL) {
				sem_wait(&syncmutex[i]);
				temp = eventHead[i];
				eventHead[i] = eventHead[i]->oNext;
				sem_post(&syncmutex[i]);
				printf("Process %d in event queue %d unblocked\n", temp->iProcessId, i);
				
				//add the process to the Ready Queue
				temp->iState = READY;
				sem_wait(&sync);
				addprocess(temp, &head, &tail);	//unblock the process and add it back to the ready queue
				sem_post(&sync);
				sem_post(&full);				//we need to post 'full' here to let consumers know a new process (the one which is blocked) is added to the list
			}	
		}
	}
}

int main() {	
	int i,j,k;
	int consumerId[NUMBER_OF_CONSUMERS];

	sem_init(&mutexResponse,0,1);		//initialize semaphore
	sem_init(&mutexTurnAround,0,1);		//initialize semaphore
	for (k=0; k<NUMBER_OF_EVENT_TYPES; k++) {
		sem_init(&syncmutex[k],0,1);	//initialize semaphore
	}
	sem_init(&mutex,0,1);				//initialize semaphore
	sem_init(&sync,0,1);				//initialize semaphore
	sem_init(&full,0,0);				//initialize semaphore
	sem_init(&empty,0, BUFFER_SIZE);	//initialize semaphore to the size of the buffer
	
	pthread_t tid[NUMBER_OF_CONSUMERS+2];
	for (i=0; i<NUMBER_OF_CONSUMERS; i++) {
		consumerId[i]=i+1;
		pthread_create(&tid[i+2], NULL, consumer, (void *)(&consumerId[i]));
	}
	pthread_create(&tid[0], NULL, producer,  NULL);
	pthread_create(&tid[1], NULL, eventmanager,  NULL);
	for (j=0; j<=NUMBER_OF_CONSUMERS+1; j++) {
		pthread_join(tid[j], NULL);
	}

	double aveResponse = (double)totalResponse/NUMBER_OF_PROCESSES;
	double aveTurnAround = (double)totalTurnAround/NUMBER_OF_PROCESSES;
	printf("Average Response Time = %f\n", aveResponse);
	printf("Average Turn Around Time = %f\n", aveTurnAround);
}