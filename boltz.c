///Program that plays boltz with N children (N provided as cmd argument)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int contains7(int x)
{
	while(x)
	{
		if(x%10 == 7)
			return 1;
		x/=10;
	}
	return 0;
}

void play(int id, int readFrom, int writeTo)
{
	int number = 1;
	srandom(time(NULL));

	while(number >= 0)
	{
		read(readFrom, &number, sizeof(int));
		if(number>=0)
		{
			int mistakeChance = rand()%10;
			number++;
			if(number%7 == 0 || contains7(number))
			{
				if(mistakeChance == 0)
				{
					printf("Process %d made a mistake: %d. Stupid process!\n",id,number);
			       		number = -1;
				}
				else
					printf("%d -- Boltz!\n",id);
			}
			else
				printf("%d -- %d\n",id,number);
		}
		else
			printf("Child %d has left the chat...\n",id);
		write(writeTo, &number, sizeof(int));
	}
		
}

int main(int argc, char **argv)
{
	if(argc<2)
		printf("You didn't provide N!\n");
	int n = atoi(argv[1]);
	int p[n][2]; //pipes for communicating between children

	for(int i=0;i<n;i++)
		pipe(p[i]);
	
	for(int i=1;i<n;i++)
	{
		int c = fork();
		if(c == 0)
		{
			// child process
			int id = i;
			int readFrom = id;
			int writeTo = (id + 1) % n;
			play(id,p[readFrom][0],p[writeTo][1]);
			exit(0);
		}
	}
	int number = 1;
	int readFrom = 0, writeTo = 1;
	
	printf("%d -- %d\n",0,number);
	write(p[writeTo][1], &number, sizeof(int));
	play(0, p[readFrom][0], p[writeTo][1]); // parent plays first

	for(int i=0;i<n;i++)
		{
			wait(0);
			close(p[i][0]);
			close(p[i][1]);
		}
	return 0;
}
