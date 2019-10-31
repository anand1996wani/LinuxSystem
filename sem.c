#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

int main(int argc,char *argv[]){
	int sem_id = semget(50,1,IPC_CREAT | 0666);
	if(sem_id == -1){
		perror("semget error");
		exit(-1);
	}
	union semun semnum;
	semnum.val = 0;
	int ret = semctl(sem_id,0,SETVAL,semnum);
	if(ret == -1){
		perror("semctl error");
		exit(-1);
	}
	struct sembuf sembuf[1];
	int childId = fork();
	if(childId == 0){
		sembuf[0].sem_num = 0;
		sembuf[0].sem_op = -1;
		sembuf[0].sem_flg = 0;
		ret = semop(sem_id,sembuf,1);
		printf("Child Process %d\n",getpid());
	}else if(childId > 0){
		sembuf[0].sem_num = 0;
		sembuf[0].sem_op = 1;
		sembuf[0].sem_flg = 0;
		ret = semop(sem_id,sembuf,1);
		printf("Parent Process %d\n",getpid());
	}else{
		perror("Fork Error");
	}
	return 0;
}
