#include <stdlib.h>
#include <sys/time.h>
#include "coursework.h"
#include <stdio.h>

struct process *head = NULL;	//Pointer to the head of the list, which stores all processes
int totalResponse=0;			//used for calculating average response time
int totalTurnAround=0;			//used for calculating average turn around time

//function used to insert processes into the Ready Queue by insertion sort
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

//funtion used to similuate the running of processes
void runprocess() {
	struct timeval start;			//stores time when the process starts to run
	struct timeval end;				//stores time when the process is finished
	struct process *temp = head;	//pointer points to the current process which needs to run
	int responseDiff = 0;			//stores the response time of the process
	int turnAroundDiff = 0;			//stores the turn around time of the process
	int preBurstTime;				//stores the process's burst time before its running

	while (head!=NULL) {
		preBurstTime = temp->iBurstTime;
		simulateSJFProcess(temp, &start, &end);
		turnAroundDiff = getDifferenceInMilliSeconds(temp->oTimeCreated, end);	//calculate response time
		responseDiff = getDifferenceInMilliSeconds(temp->oTimeCreated, start);	//calculate turn around time
		printf("Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Response Time = %d, Turn Around Time = %d\n", temp->iProcessId, preBurstTime, temp->iBurstTime, responseDiff, turnAroundDiff);
		totalResponse = totalResponse + responseDiff;
		totalTurnAround = totalTurnAround + turnAroundDiff;
		head = head->oNext;
		free(temp);		//free unneeded buffer
		temp = head;		
	}
}

int main() {
	int i;		//local counter for the loop
	for (i=0; i<NUMBER_OF_PROCESSES; i++) {
		struct process *newprocess = generateProcess();
		addprocess(newprocess);
	}
	runprocess();
	double aveResponse = (double)totalResponse/NUMBER_OF_PROCESSES;			//calculate the average response time
	double aveTurnAround = (double)totalTurnAround/NUMBER_OF_PROCESSES;		//calcualte the average turn around time
	printf("Average Response Time = %f\n", aveResponse);
	printf("Average Turn Around Time = %f\n", aveTurnAround);
}