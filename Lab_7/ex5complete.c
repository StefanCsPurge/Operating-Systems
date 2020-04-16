/*    Scrieți un program ce primește doi parametri: un cuvant și un nume de fișier. 
 *    Va rula grep pentru a extrage liniile ce conțin cuvantul dat din fișier și 
 *    va afișa dintre acele linii doar cele ce au lungime multiplu de 3 
 *    (fork + dup2 + exec, read, strlen). */


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int p2g[2],g2p[2];
	if(pipe(p2g)<0){
		perror("Unable to create p2g pipe");
		exit(1);
	}
	if(pipe(g2p)<0){
		perror("Unable to create g2p pipe");
		exit(2);
	}
	int f=fork();
	if (f<0){
		perror("Unable to create a child process");
		exit(3);
	}
	if(f == 0){
		close(g2p[0]); close(p2g[1]);
		int wordLen, wordReadLen;
		if (read(p2g[0],&wordLen,sizeof(int))<0){
			perror("Unable to read the size of the word");
			exit(4);
		}
		//printf("Child received wordLen: %d\n",wordLen);
		char *word=(char*)malloc(wordLen+1);
		if((wordReadLen=read(p2g[0],word,wordLen))<0){
			perror("Unable to read the word");
			exit(4);
		}
		if (wordLen!=wordReadLen){
			printf("Received %d, but was supposed to received %d. Implement a retry logic!\n", wordReadLen, wordLen);
			perror("The received word len is different than what was received");
			exit(4);
		}
		word[wordReadLen]=0;
		//printf("Child received word: %s\n",word);
		int fileNameLen, fileNameRead;
		if (read(p2g[0],&fileNameLen,sizeof(int))<0){
			perror("Unable to read the size of the fileName");
			exit(5);
		}
		//printf("Child received fileNameLen: %d\n",fileNameLen);
		char *fileName=(char*)malloc(fileNameLen+1);
		if((fileNameRead=read(p2g[0],fileName,fileNameLen))<0){
			perror("Unable to read the fileName");
			exit(5);
		}
		if (fileNameLen!=fileNameRead){
			printf("Received %d, but was supposed to received %d. Implement a retry logic!\n", fileNameLen,fileNameRead);
			perror("The received fileName len is different than what was received");
			exit(5);
		}
		fileName[fileNameRead]=0;
		//printf("Child received fileName: %s\n",fileName);
		close(p2g[0]);
		//printf("Executing: grep with word: %s and file: %s\n", word, fileName);
		dup2(g2p[1],1);
		if (execlp("grep","grep",word,fileName,NULL)<0){
			perror("Unable to execute the command");
			free(word);
			free(fileName);
			exit(6);
		} 
		// the result of this will go in p2g[1] writing buffer
		//   // no need of a exit here since the process is overriden by the exec command
		//     //exit(1);
	}
	close(p2g[0]); close(g2p[1]);
	char *word=(char*)malloc(sizeof(char)*56);
	char *fileName=(char*)malloc(sizeof(char)*56);
	printf("Insert file name (up to 55 characters): "); 
	scanf("%55s",fileName);
	printf("Insert the word you want to search for (up to 55 characters): "); 
	scanf("%55s",word);
	int n = strlen(word);
	int nFile= strlen(fileName);
	if (write(p2g[1],&n,sizeof(int))<0){
		perror("Unable to send the word length to the child");
		exit(7);
	}
	int wb;
	if ((wb=write(p2g[1],word,n))<n){
		perror("Unable to send the word to the child");
		exit(7);
	}
	if (write(p2g[1],&nFile,sizeof(int))<0){
		perror("Unable to send the fileName length to the child");
		exit(8);
	}
	if ((wb=write(p2g[1],fileName,nFile))<n){
		perror("Unable to send the fileName to the child");
		exit(8);
	}
	close(p2g[1]);
	char *content=(char*)malloc(1001);
	int rb;
	if((rb=read(g2p[0],content,1000))>0){ // the lines given by grep
		content[rb]=0;
		//Here we need to check if we have lines of the requested length.
		//printf("Received from child:\n %s %ld\n",content,strlen(content));
		printf("The lines that have their length divisible with 3 are:\n");
		char *t = strtok(content,"\n");
		while(t)
		{
			if(strlen(t) % 3 == 0)
				printf("%s\n",t);
			t = strtok(0,"\n");
		}
	}
	free(content);
	free(word);
	free(fileName);
	return 0;
} 
