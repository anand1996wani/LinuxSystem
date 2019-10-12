/*

exec_pipe


*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX 100

void normal_task(char input[MAX]){
	char *pass[10];
	char *token = strtok(input," ");
	int num_of_args = 0;
	while(token != NULL){
		pass[num_of_args] = token;
		printf("%s ",pass[num_of_args]);
		num_of_args++;
		token = strtok(NULL," ");
	}
	pass[num_of_args] = NULL;
	printf("\n");
	execvp(pass[0],pass);
}

void pipe_to_do(char input1[MAX],char input2[MAX]){
	char *pass1[10], *pass2[10];
	char *token1 = strtok(input1," ");
	int num_of_args = 0;
	while(token1 != NULL){
		pass1[num_of_args] = token1;
		printf("%s ",pass1[num_of_args]);
		num_of_args++;
		token1 = strtok(NULL," ");
	}
	pass1[num_of_args] = NULL;
	printf("\n");

	char *token2 = strtok(input2," ");
	num_of_args = 0;
	while(token2 != NULL){
		pass2[num_of_args] = token2;
		printf("%s ",pass2[num_of_args]);
		num_of_args++;
		token2 = strtok(NULL," ");
	}
	pass2[num_of_args] = NULL;
	printf("\n");

	int p[2];
	pipe(p);
	int ret = fork();
	if(ret == 0){
		close(p[0]);
		dup2(p[1],1);
		execvp(pass1[0],pass1);
	}
	wait(NULL);
	close(p[1]);
	dup2(p[0],0);
	execvp(pass2[0],pass2);
}

void pipe_task(char input[MAX]){
	char *pass[10];
	char *token = strtok(input,"|");
	int num_of_args = 0;
	while(token != NULL){
		pass[num_of_args] = token;
		num_of_args++;
		token = strtok(NULL,"|");
	}
	pass[num_of_args] = NULL;
	
	pipe_to_do(pass[0],pass[1]);
}


int main(int argc,char *argv[]){
	char input[MAX];
	printf("shell>\n");
	fgets(input,100,stdin);
	int len = 0;
	len = strlen(input);
	input[len - 1] = '\0';

	if(strstr(input,"|") != NULL){
		pipe_task(input);
	}else{
		normal_task(input);
	}

	return 0;
}
