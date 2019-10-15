#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

struct voting{
	int vote;
};

struct mbuf{
	long mtype;
	struct voting vote;
}msgBuf;

void childProcess(int qid){
	msgBuf.mtype = getpid();
	msgBuf.vote.vote = getpid()%2;
	msgsnd(qid,&msgBuf,sizeof(msgBuf) - sizeof(long),0);
	exit(0);
}

int main(int argc, char * argv[]){
	int qid = msgget(5555,IPC_CREAT | 0666);
	int pid[5];
	for(int i = 0; i < 5;i++){
		int childId = fork();
		if(childId == 0){
			childProcess(qid);
		}else{
			pid[i] = childId;
		}
	}
	
	for(int i = 0;i < 5;i++){
		waitpid(pid[i],NULL,0);
	}
	int one = 0,zero = 0;
	for(int i = 0; i < 5;i++){
		msgrcv(qid,&msgBuf,sizeof(msgBuf) - sizeof(long),pid[i],0);
		if(msgBuf.vote.vote == 0){
			zero++;
		}else if(msgBuf.vote.vote == 1){
			one++;
		}
	}
	if(one > zero){
		printf("Result Is 1\n");
	}else{
		printf("Result Is 0\n");
	}
	return 0;
}
