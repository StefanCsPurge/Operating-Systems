#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc, char** argv){
	int pid = fork();
	if(!pid){
		printf("Child only code\n");
		sleep(10);
		exit(0);
	}
	sleep(15);
	printf("Parent-only code\n");
	wait(0);
	return 0;
}

