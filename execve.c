//File execve.c 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sigintHandler(int signum){
	printf("SigInt Received\n");
}

int main(int argc, char *argv[]){
	signal(SIGINT,sigintHandler);
	printf("Before Execve PID %d \n",getpid());
	char *argVec[10];
	char *path = "/home/anand/run";
	argVec[0] = "run";
	argVec[1] = "anand";
	argVec[2] = NULL;
	execve(path,argVec,NULL);
	perror("Execve Error\n");
	return 0;
}
