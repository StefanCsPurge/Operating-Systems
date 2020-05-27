#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

void processB()
{
	int d = open("myfifo",O_RDONLY);
	int n,x,nr=0,sum=0;
	if(read(d,&n,sizeof(int)) < 0)
	{
		perror("Read failed!");
		exit(1);
	}
	while(read(d,&x,sizeof(int)))
	{
		if(n%x == 0)
		{
			nr++;
			sum += x;
		}
	}
	close(d);
	printf("In B: %d numbers are div with %d\n",nr,n);
	
	d = open("myfifo",O_WRONLY);
	if (write(d,&sum,sizeof(int)) < 0)
	{
		perror("Write failed!");
		exit(1);
	}
	close(d);
	exit(0);
}

int main()
{
	mkfifo("myfifo",0600);
	if(fork() == 0)
		processB();
	
	//process A
	int d = open("myfifo",O_WRONLY);

	int n, x;
	printf("N = ");
	scanf("%d",&n);
	write(d,&n,sizeof(int));

	printf("Enter number: ");
	scanf("%d",&x);
	while(x)
	{
		write(d,&x,sizeof(int));
		printf("Enter number: ");
		scanf("%d",&x);
	}
	close(d);
	

	d = open("myfifo",O_RDONLY);
	int sum = 0;
	if(read(d,&sum, sizeof(int)) < 0)
	{
		perror("Read failed!");
		exit(1);
	}
	printf("The sum is %d\n",sum);
	
	close(d);
	wait(0);
	unlink("myfifo");
	return 0;
}





