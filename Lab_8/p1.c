//Program that creates 5 threads, giving each thread a string as parameter. 
//Each thread will count and add to the global variables v and n as follows: 
//the number of vowels contained by the string added to v, 
//and the number of digits contained in the string added to n

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int v=0,n=0;
pthread_mutex_t mutex;

void* threadFunction(void *param)
{
	char* string = (char*)param;
	int voc=0,nr=0,len=strlen(string);
	for(int i=0;i<len;i++)
		if(strchr("aeiouAEIOU",string[i]))
			voc++;
		else if(string[i]>='0' && string[i]<='9')
			nr++;
	printf("%s %d %d\n",string,voc,nr);
	
	pthread_mutex_lock(&mutex);
	v+=voc;
	pthread_mutex_unlock(&mutex);

	pthread_mutex_lock(&mutex);
	n+=nr;
	pthread_mutex_unlock(&mutex);

	return NULL;
}

int main(int argc, char** argv)
{
	if(argc<6)
	{
		printf("Please provide 5 strings as arguments!\n");
		exit(-1);
	}
	//for(int i=1;i<argc;i++)
	//	printf("%s ",argv[i]);
	//printf("\n");
	pthread_t thr[5];

	for(int i=0;i<5;i++)
		pthread_create(&thr[i],NULL,threadFunction,argv[i+1]);
	
	for(int i=0;i<5;i++)
		pthread_join(thr[i],NULL);

	pthread_mutex_destroy(&mutex);
	
	printf("The total number of vowels is %d\n",v);
	printf("The total number of digits is %d\n",n);
	return 0;
}
