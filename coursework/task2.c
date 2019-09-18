#include <stdlib.h>
#include <sys/time.h>
#include "coursework.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t empty;				//semaphore used to control the producer
sem_t full;					//semaphore used to control the consumer
sem_t sync;					//semaphore used to prevent multiple threads entering the critical section
struct process *head=NULL;	//Pointer to the head of the list, which stores all processes
int totalResponse=0;		//used for calculating average response time
int totalTurnAround=0;		//used for calculating average turn around time

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
void * consumer(void * h) {	
	struct timeval start;			//stores time when the process starts to run
	struct timeval end;				//stores time when the process is finished
	int responseDiff = 0;			//stores the response time of the process
	int turnAroundDiff = 0;			//stores the turn around time of the process
	int preBurstTime;				//stores the process's burst time before its running
	struct process *temp;			//pointer points to the current process which needs to run
	int counter=0;					//counter for the loop
	while (counter < NUMBER_OF_PROCESSES) {
		sem_wait(&full);			//everytime a process is consumed, value of semaphore 'full' will be decreased by 1
		sem_wait(&sync);			//everytime a thread enters the critical section, value of semaphore 'sync' will be decreased to 0
	
		temp = head;				//store the process into a temporary pointer
		head = head->oNext;			//move the process out of the list
		counter = counter+1;	
	
		sem_post(&sync);			//everytime a thread quits the critical section, value of semaphore 'sync' will increased to 1
		sem_post(&empty);			//everytime a process is consumed, value of semaphore 'empty' will be increased by 1

		preBurstTime = temp->iBurstTime;
		simulateSJFProcess(temp, &start, &end);
		turnAroundDiff = getDifferenceInMilliSeconds(temp->oTimeCreated, end);
		responseDiff = getDifferenceInMilliSeconds(temp->oTimeCreated, start);
		printf("Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Response Time = %d, Turn Around Time = %d\n", temp->iProcessId, preBurstTime, temp->iBurstTime,responseDiff, turnAroundDiff);
		totalResponse = totalResponse + responseDiff;
		totalTurnAround = totalTurnAround + turnAroundDiff;
		free(temp);					//free the process which has been run
	}
}

//producer thread
void * producer(void * h) {
	int counter=0;				//counter for the loop
	while (counter < NUMBER_OF_PROCESSES) {
		struct process *newprocess = generateProcess();
		sem_wait(&empty);		//everytime a process is produced, value of semaphore 'empty' will be decreased by 1
		sem_wait(&sync);		//everytime a thread enters the critical section, value of semaphore 'sync' will be decreased to 0
			
		addprocess(newprocess);
		counter = counter+1;
		
		sem_post(&sync);		//everytime a thread quits the critical section, value of semaphore 'sync' will increased to 1
		sem_post(&full);		//everytime a process is produced, value of semaphore 'full' will be increased by 1
	}
}

int main() {
	sem_init(&sync,0,1);				//initialize semaphore
	sem_init(&full,0,0);				//initialize semaphore
	sem_init(&empty,0, BUFFER_SIZE);	//initialize semaphore to the size of the buffer
	
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, producer,  NULL);	//create the producer thread
	pthread_create(&tid2, NULL, consumer, NULL);	//create the consumer thread
	pthread_join(tid1, NULL);						//let the main function wait until the consumer thread is finished
	pthread_join(tid2, NULL);						//let the main function wait until the producer thread is finished

	double aveResponse = (double)totalResponse/NUMBER_OF_PROCESSES;			//calculate the average response time
	double aveTurnAround = (double)totalTurnAround/NUMBER_OF_PROCESSES;		//calcualte the average turn around time
	printf("Average Response Time = %f\n", aveResponse);
	printf("Average Turn Around Time = %f\n", aveTurnAround);
}