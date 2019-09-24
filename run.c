//File run.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[]){

	printf("After Exec Inside Run Program %d\n",getpid());
	printf("My command line argument is %s\n",argv[1]);
	return 0;
}
