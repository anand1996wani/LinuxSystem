#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
int i = 0;
void sigusr1Handler(int signum){
	printf("%d PID is %d\n",i,getpid());
}
int main(){
	signal(SIGUSR1,sigusr1Handler);
	sigset_t signalMask,emptyMask;
	sigemptyset(&signalMask);
	sigemptyset(&emptyMask);
	sigaddset(&signalMask,SIGUSR1);
	int ret = sigprocmask(SIG_BLOCK,&signalMask,NULL);
	int childId = fork();
	if(childId == -1){
		perror("Fork Error\n");
	}else if(childId == 0){
		//child code
		for(i = 0; i < 5000;i++){
			kill(getppid(),SIGUSR1);
			sigsuspend(&emptyMask);
		}
	}else{
		//parent code
		for(i = 0; i < 5000;i++){
			sigsuspend(&emptyMask);
			kill(childId,SIGUSR1);
		}
	}
	return 0;
}
