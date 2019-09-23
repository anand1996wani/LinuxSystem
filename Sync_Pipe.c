#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int i = 0;
int main(){
	int myPipe1[2],myPipe2[2];
	pipe(myPipe1);
	pipe(myPipe2);
	int childId = fork();
	if(childId == 0){
		for(i = 0;i < 5000;i++){
			char message[] = "Child";
			write(myPipe1[1],message,sizeof(message));
			char data[50];			
			read(myPipe2[0],data,sizeof(data));
			printf("%d %s\n",i,data);
		}
	}else{
		for(i = 0; i < 5000;i++){
			char message[] = "Parent";
			char data[50];
			read(myPipe1[0],data,sizeof(data));
			printf("%d %s\n",i,data);
			write(myPipe2[1],message,sizeof(message));
		}
	}
	return 0;
}
