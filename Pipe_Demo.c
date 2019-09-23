#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
	int myPipe1[2];
	pipe(myPipe1);
	int myPipe2[2];
	pipe(myPipe2);
	int childPID = fork();
	if(childPID == -1){
		perror("Child Error\n");
	}else if(childPID == 0){
		//Child Process
		char message[100];
		while(1){
			read(myPipe1[0],message,sizeof(message));
			printf("PID %d %s",getpid(),message);
			scanf("%s",message);
			write(myPipe2[1],message,sizeof(message));
		}
	}else{
		//Parent Process
		char message[100];
		while(1){
			scanf("%s",message);
			write(myPipe1[1],message,sizeof(message));
			read(myPipe2[0],message,sizeof(message));
			printf("PID %d %s",getpid(),message);
		}
	}
	return 0;
}
