#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int n = 0;
void myHandler(int sigNum){
	if(n != 0){
		alarm(1);
		n = n - 1;
	}else{
		raise(SIGINT);
	}
}

int main(){
	printf("Hello World\n");
	signal(SIGALRM,myHandler);
	printf("Enter the time for sleep\n");
	scanf("%d",&n);
	alarm(1);
	while(1){
		pause();	
	}

	return 0;
}
