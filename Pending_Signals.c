#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void sigint_Handler(int signum){
	printf("SIGINT Received\n");	
}
void  sigusr1_Handler(int signum){
	printf("SIGUSR1 Received\n");	
}
int main(){
	printf("Hello World\n");
	signal(SIGINT,sigint_Handler);
	signal(SIGUSR1,sigusr1_Handler);
	sigset_t signalSet;
	sigemptyset(&signalSet);
	sigaddset(&signalSet,SIGINT);
	sigaddset(&signalSet,SIGUSR1);
	int ret = sigprocmask(SIG_BLOCK,&signalSet,NULL);//blocking the signals
	if(ret==-1){
		perror("Error In signal Blocking\n");
	}
	sigset_t waiting;
	sleep(25);
	sigpending(&waiting);//checking pending signals
	if(sigismember(&waiting,SIGINT)){
		printf("SIGINT is pending\n");
	}
	if(sigismember(&waiting,SIGUSR1)){
		printf("SIGUSR1 is pending\n");
	}
	ret = sigprocmask(SIG_UNBLOCK,&signalSet,NULL);//Unblocking the signal
	if(ret == -1){
		perror("Error in signal UnBlocking\n");
	} 
	return 0;
}
