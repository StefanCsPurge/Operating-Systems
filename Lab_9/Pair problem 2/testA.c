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

// A creates a child process that reads from parent through pipe a file name
// and computes 5 numbers that represent the frequency of every vowel to B 
// and B prints these freqencies

int main()
{
	char* fileName = "a.txt";
	int p2c[2];
	pipe(p2c);

	if(fork() == 0)
	{
		close(p2c[1]);
		char fileName[55];

		read(p2c[0],fileName,55);
		close(p2c[0]);
		FILE *f = fopen(fileName,"r");
		// a e i o u
		int ca=0,ce=0,ci=0,co=0,cu=0;
		char c;
		while((c = fgetc(f)) != EOF)
		{
			if( c == 'A' || c == 'a')
				ca++;
			else if (c == 'E' || c == 'e')
				ce++;
			else if(c == 'I' || c == 'i')
				ci++;
			else if (c == 'O' || c == 'o')
				co++;
			else if (c == 'U' || c == 'u')
				cu++;
		}
		mkfifo("myfifo",0600);
		int fd = open("myfifo",O_WRONLY);
		write(fd,&ca,sizeof(int));
		write(fd,&ce,sizeof(int));
		write(fd,&ci,sizeof(int));
		write(fd,&co,sizeof(int));
		write(fd,&cu,sizeof(int));
		close(fd);
		exit(0);
	}

	close(p2c[0]);
	write(p2c[1],fileName,55);
	wait(0);
	return 0;
}

		
