//Sau un program care creeaza doua  procese copil care comunicau intre ele prin fifo/pipe si citeai 
//un string in ala care incepea programu si trimiteai la celalalt care stergea primu caracter 
//dupa trimitea stringu la primu iar si stergea ultimele doua caractere si 
//tot asa pana ramanea stringu cu 3 caractere

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
	int p2a[2],a2p[2];
	if(pipe(p2a) == -1)
	{
		perror("Error in pipe");
		exit(1);
	}
	if(pipe(a2p) == -1)
	{
		perror("Error on pipe 2");
		exit(1);
	}

	int f = fork();
	if(f == -1)
	{
		perror("Error on fork");
		exit(1);
	}

	if(f == 0)
	{
		//second child motherfucker
		close(p2a[1]); close(a2p[0]);
		int len;
		char* ma_string = malloc(111 * sizeof(char));
		if(read(p2a[0],&len,sizeof(int)) < 0){
				perror("Error on pipe read 1");
				exit(3);
		}
		if(read(p2a[0],ma_string,111) < 0){
				perror("Error on pipe read 2");
				exit(3);
		}
		
		while(strlen(ma_string) > 3)
		{	
			// now delete the char from the front
			ma_string++;
			len--;
			printf("Process %d : %s\n", getpid(), ma_string);

			if(write(a2p[1],&len,sizeof(int)) < 0)
			{
				perror("Error on pipe write");
				exit(3);
			}
			if(write(a2p[1],ma_string,111) < 0)
			{
				perror("Error in pipe write");
				exit(3);
			}
			
			if(len<=3) break;	
			if(read(p2a[0],&len,sizeof(int)) < 0){
				perror("Error on pipe read 1");
				exit(3);
			}
			if(read(p2a[0],ma_string,111) < 0){
				perror("Error on pipe read 2");
				exit(3);
			}
		}
		close(p2a[0]); close(a2p[1]);
		exit(0);
	}

	f = fork();
	if(f == -1)
	{
		perror("Error on fork");
		exit(1);
	}
	
	if(f==0)
	{
		// first child motherfucker
		char string[111];
		printf("Enter string: ");
		scanf("%[^\n]",string);
		close(p2a[0]); close(a2p[1]);
		char* ma_string = malloc(111 * sizeof(char));
		strcpy(ma_string,string);

		while(strlen(ma_string)  > 3)
		{
			int len = strlen(ma_string);
			len--;
			ma_string[len] = '\0'; // get last char out 
			printf("Process %d : %s\n", getpid(), ma_string);

			if(write(p2a[1],&len,sizeof(int)) < 0)
			{
				perror("Error on pipe write!");
				exit(2);
			}
			if(write(p2a[1],ma_string,111) < 0)
			{
				perror("Error on pipe write");
				exit(2);
			}

			if(len <=3) break; 
			if(read(a2p[0],&len,sizeof(int)) < 0)
			{
				perror("Error on pipe read");
				exit(3);
			}
			if(read(a2p[0],ma_string,111) < 0)
			{
				perror("Error on pipe read");
				exit(3);
			}
		}
		close(p2a[1]); close(a2p[0]);	
		exit(0);
	}
	
					
	wait(0); wait(0);
	return 0;
}

