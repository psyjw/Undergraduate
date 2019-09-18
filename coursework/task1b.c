#include <stdlib.h>
#include <sys/time.h>
#include "coursework.h"
#include <stdio.h>

struct process *head = NULL;			//Pointer to the head of the list, which stores all processes
struct process *tail = NULL;			//Pointer to the tail of the list, which stores all processes
int totalResponse=0;					//used for calculating average response time
int totalTurnAround=0;					//used for calculating average turn around time
int runTime[NUMBER_OF_PROCESSES]={0};	//used for counting how many times a process is run

//function used to insert processes into the Ready Queue
void addprocess(struct process *newprocess) {
	//add the process to the Ready Queue
	newprocess->iState = READY;
	//if there is no process in the list
	if (head==NULL) {
		head = newprocess;
		tail = newprocess;
	}
	else {
		tail->oNext = newprocess;		//add the process to the end of the list
		tail = tail->oNext;				//let the 'tail' pointer points to the end of the list
		tail->oNext = NULL;
	}
}

//funtion used to similuate the running of processes
void runprocess() {
	struct timeval start;			//stores time when the process starts to run
	struct timeval end;				//stores time when the process is finished
	int preBurstTime;				//stores the process's burst time before its running
	int responseDiff = 0;			//stores the response time of the process
	int turnAroundDiff = 0;			//stores the turn around time of the process
	struct process *temp;			//pointer points to the current process which needs to run
	while (head != NULL) {
		temp=head;
		preBurstTime = temp->iBurstTime;
		simulateRoundRobinProcess(temp, &start, &end);
		turnAroundDiff = getDifferenceInMilliSeconds(temp->oTimeCreated, end);
		responseDiff = getDifferenceInMilliSeconds(temp->oTimeCreated, start);
		runTime[temp->iProcessId]=runTime[temp->iProcessId]+1;
		//when a process is the first time to run and its burst time is more than the time slice
		if ((runTime[temp->iProcessId]==1)&&(temp->iState == READY)) {
			printf("Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Response Time = %d\n", temp->iProcessId, preBurstTime, temp->iBurstTime, responseDiff);
			totalResponse = totalResponse + responseDiff;
			head=head->oNext;
			addprocess(temp);
		}
		//when a process is the first time to run and its burst time is less than the time slice
		else if ((runTime[temp->iProcessId]==1)&&(temp->iState == FINISHED)){
			printf("Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Response Time = %d, Turn Around Time = %d\n", temp->iProcessId, preBurstTime, temp->iBurstTime, responseDiff, turnAroundDiff);
			totalResponse = totalResponse + responseDiff;
			totalTurnAround = totalTurnAround + turnAroundDiff;
			head=head->oNext;
			free(temp);
		}
		//when a process is not the first time to run and its remaining burst time is more than the time slice
		else if ((runTime[temp->iProcessId]!=1)&&(temp->iState == READY)) {
			printf("Process Id = %d, Previous Burst Time = %d, New Burst Time = %d\n", temp->iProcessId, preBurstTime, temp->iBurstTime);
			head=head->oNext;
			addprocess(temp);
		}
		//when a process is not the first time to run and its remaining burst time is less than the time slice
		else if ((runTime[temp->iProcessId]!=1)&&(temp->iState == FINISHED)) {
			printf("Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Turn Around Time = %d\n", temp->iProcessId, preBurstTime, temp->iBurstTime, turnAroundDiff);
			totalTurnAround = totalTurnAround + turnAroundDiff;
			head=head->oNext;
			free(temp);
		}
	}
}

int main() {	
	int i;		//counter for the loop
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