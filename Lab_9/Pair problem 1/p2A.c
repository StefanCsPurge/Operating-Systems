#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>


int main()
{
	int A2B[2];
	if(pipe(A2B) == -1)
	{
		perror("Error on pipe");
		exit(1);
	}

	char* file = "numbers.txt";

	int f = fork();
	if(f == -1)
	{
		perror("Error on fork");
		exit(1);
	}

	if(f==0)
	{
		// p1
		close(A2B[0]);
		int n = 0,x;
		printf("n=");
		scanf("%d",&n);
		if(write(A2B[1],&n,sizeof(int)) < 0){
			perror("Error on pipe write");
			exit(2);
		}	

		FILE* f = fopen(file,"r");
		for(int i=0;i<n;i++)
		{
			if(fscanf(f,"%d",&x)<0)
			{
				perror("Failed to read from file!");
				exit(2);
			}
			if(write(A2B[1],&x,sizeof(int)) < 0){
				perror("Error on pipe write");
				exit(2);
			}	
		}
		fclose(f);
		close(A2B[1]);
		exit(0);
	}

	f = fork();
	if(f == -1)
	{
		perror("Error on fork");
		exit(1);
	}
	if(f == 0)
	{
		// p2
		close(A2B[1]);
		int oddSum = 0,n,x;

		if(read(A2B[0],&n,sizeof(int)) < 0)
		{
			perror("Error on pipe read");
			exit(3);
		}

		for(int i=0;i<n;i++)
		{
			if(read(A2B[0],&x,sizeof(int)) < 0)
			{
				perror("Error on pipe read");
				exit(3);
			}
			if(x%2)
				oddSum += x;
		}
		close(A2B[0]);

		if(mkfifo("myfifo",0600) < 0){
			perror("Error on creating fifo!");
			exit(4);
		}
		int fd;

		if((fd = open("myfifo",O_WRONLY)) < 0){
			perror("Error on opening fifo");
			exit(4);
		}
		if(write(fd, &oddSum , sizeof(int)) < 0)
		{
			perror("Error on write to fifo");
			exit(4);
		}
		close(fd);
		exit(0);
	}
	wait(0); 
	wait(0);
	return 0;
}
