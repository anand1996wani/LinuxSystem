#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char *argv[]){
	int myPipe1[2],myPipe2[2];
	pipe(myPipe1);
	pipe(myPipe2);
	char array[50];
	printf("Enter the string\n");
	scanf("%s",array);
	write(myPipe1[1],array,sizeof(array));
	int childId = 0;
	childId = fork();
	if(childId == -1){
		perror("Fork Error\n");
	}else if(childId == 0){
		close(0);
		int ret = dup2(myPipe1[0],0);//myPipe1 will point to standard input
		if(ret == -1){
			perror("dup2 error\n");
		}
		char message[50];
		read(0,message,sizeof(message));
		int j = 0;
		printf("I am Child Process PID %d Message Received from Parent Process is %s\n",getpid(),message);
		while(message[j]!='\n'){
			message[j] = toupper(message[j]);
			j++;
		}
		close(1);
		ret = dup2(myPipe2[1],1);//myPipe2 will point to standard output
		write(1,message,sizeof(message));
		exit(0);
	}else{
		char message[50];
		read(myPipe2[0],message,sizeof(message));
		printf("I am Parent Process PID %d Message Received from Child Process %s\n",getpid(),message);
		int status;
		wait(&status);//To avoid making zombie
	}return 0;}
