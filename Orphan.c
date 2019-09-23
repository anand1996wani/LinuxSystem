#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[]){
	int pid = 0;
	pid = fork();
	if(pid == -1){
		perror("Fork Error\n");
	}else if(pid == 0){
		printf("I am Child Process PID is %d my  Parent PID is %d\n",getpid(),getppid());
		system("ps -elf | grep a.out");
		sleep(5);
		printf("After Sleep Child Process PID is %d Parent PID is %d\n",getpid(),getppid());
		system("ps -elf | grep a.out");
		sleep(5);
	}else{
		printf("I am Parent Process PID is %d Parent PID is %d\n",getpid(),getppid());
		sleep(2);
	}

	return 0;
}
