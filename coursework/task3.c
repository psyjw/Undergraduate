#include <stdlib.h>
#include <sys/time.h>
#include "coursework.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t empty;						//semaphore used to control the producer
sem_t full;							//semaphore used to control the consumer
sem_t sync;							//semaphore used to prevent multiple threads entering the critical section
sem_t mutex;						//semaphore used to prevent multiple consumers going asleep before the producer quits
sem_t mutexTime;					//semaphore used to prevent multiple consmuers modifying total response time and turn around time
struct process *head=NULL;			//Pointer to the head of the list, which stores all processes
int totalResponse=0;				//used for calculating average response time
int totalTurnAround=0;				//used for calculating average turn around time
int counter=NUMBER_OF_PROCESSES;	//used for recording number of consumed processes

//function used to generate new processes and insert them into the list by insertion sort
void addprocess(struct process *newprocess) {
	//add the process to the Ready Queue
	newprocess->iState = READY;
	//if there is no process in the list
	if (head==NULL) {
		head = newprocess;
	}
	//if the new added process's burst time is less than the first process's burst time
	else if (newprocess->iBurstTime <= head->iBurstTime) {
		newprocess->oNext = head;
		head = newprocess;
	}
	//insertion sort
	else {
		struct process *cur = head;
		struct process *temp = head;
		while (cur!=NULL) {
			if (newprocess->iBurstTime <= cur->iBurstTime) {
				newprocess->oNext = cur;
				temp->oNext = newprocess;
				break;
			}
			temp = cur;
			cur = cur->oNext;
		}
		if (cur == NULL) {
			temp->oNext = newprocess;
		}
	}
}

//consumer thread
void * consumer(void* h) {
	int consumerId=*((int*)h);	//record current consumer's ID

	struct timeval start;		//stores time when the process starts to run
	struct timeval end;			//stores time when the process is finished
	int responseDiff = 0;		//stores the response time of the process
	int turnAroundDiff = 0;		//stores the turn around time of the process
	int preBurstTime;			//stores the process's burst time before its running
	struct process *temp;		//pointer points to the current process which needs to run
	
	while (1) {
		sem_wait(&mutex);		
		counter = counter-1;	//prevent multiple consumer threads from being slept by semaphore 'full'
		if (counter < 0) {		//because when producer cannot produce processes any more, semaphore 'full' cannot increase
			sem_post(&mutex);	//thus these sleeping consumer cannot be waken up
			return;				//so we need to finish these consumers before they enter semaphore 'full' to prevent deadlock
		}
		sem_post(&mutex);
			
		sem_wait(&full);
		sem_wait(&sync);
		
		temp=head;				//store the process into a temporary pointer
		head=head->oNext;		//move the process out of the list	
		
		sem_post(&sync);
		sem_post(&empty);

		preBurstTime = temp->iBurstTime;
		simulateSJFProcess(temp, &start, &end);
		turnAroundDiff = getDifferenceInMilliSeconds(temp->oTimeCreated, end);
		responseDiff = getDifferenceInMilliSeconds(temp->oTimeCreated, start);
		printf("Consumer Id = %d, Process Id = %d, Previous Burst Time = %d, New Burst Time = 0, Response Time = %d, Turn Around Time = %d\n", consumerId, temp->iProcessId, preBurstTime, responseDiff, turnAroundDiff);
		
		sem_wait(&mutexTime);
		totalResponse = totalResponse + responseDiff;
		totalTurnAround = totalTurnAround + turnAroundDiff;
		sem_post(&mutexTime);
		free(temp);				//free the process which has been run
	}
}

//producer thread
void * producer(void *h) {
	int c=0;					//local counter for the loop
	while (c < NUMBER_OF_PROCESSES) {
		struct process *newprocess = generateProcess();

		sem_wait(&empty);		
		sem_wait(&sync);		

		addprocess(newprocess);
		c=c+1;
		
		sem_post(&sync);		
		sem_post(&full);		
	}
}

int main() {
	int i,j;								//counter for loops to create and wait threads
	int consumerId[NUMBER_OF_CONSUMERS];	//array for storing and passing different consumers' ID

	sem_init(&sync,0,1);					//initialize semaphore
	sem_init(&mutexTime,0,1);				//initialize semaphore
	sem_init(&mutex,0,1);					//initialize semaphore
	sem_init(&full,0,0);					//initialize semaphore
	sem_init(&empty,0, BUFFER_SIZE);		//initialize semaphore to the size of the buffer
	
	//create the producer and consumer threads
	pthread_t tid[NUMBER_OF_CONSUMERS+1];
	for (i=0; i<NUMBER_OF_CONSUMERS; i++) {
		consumerId[i]=i+1;
		pthread_create(&tid[i+1], NULL, consumer, (void *)(&consumerId[i]));
	}
	pthread_create(&tid[0], NULL, producer,  NULL);
	//let the main function wait until the producer and consumer threads are finished
	for (j=0; j<=NUMBER_OF_CONSUMERS; j++) {
		pthread_join(tid[j], NULL);
	}

	double aveResponse = (double)totalResponse/NUMBER_OF_PROCESSES;			//calculate the average response time
	double aveTurnAround = (double)totalTurnAround/NUMBER_OF_PROCESSES;		//calcualte the average turn around time
	printf("Average Response Time = %f\n", aveResponse);
	printf("Average Turn Around Time = %f\n", aveTurnAround);
}

