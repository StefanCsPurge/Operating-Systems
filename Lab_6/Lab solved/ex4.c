/// Scrieți un program care fork()-uie procese copil recursiv cată vreme PID-ul fiecărui copil e par.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void fork_on_even_pid(int pid)
{
	if(pid % 2)
		return;
	int ID = fork();
	if(!ID)
	{
		printf("Current PID is %d\n",getpid());
		fork_on_even_pid(getpid());
		exit(0);
	}
	printf("%d ended\n",ID);
	wait(0);
}

int main()
{
	fork_on_even_pid(0);
	return 0;
}

