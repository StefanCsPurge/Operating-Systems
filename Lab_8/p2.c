//A C program receives command line args numbers, and creates for each 
//a thread that checks if the numbers are multiple of 2 or 5, 
//incrementing a global variable. (use atoi) 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int gVar=0;

pthread_mutex_t mutex;

void* checkMultiple(void *param)
{
	int x = *(int*)param;
       	free(param);	
	if(x%2==0 || x%5==0)
	{
		pthread_mutex_lock(&mutex);
		gVar++;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main(int argc, char** argv)
{
	pthread_t* thr = malloc(sizeof(pthread_t)*argc);
	for(int i=1;i<argc;i++)
	{
		int* number = (int*)malloc(sizeof(int));
		*number = atoi(argv[i]);
		pthread_create(&thr[i],NULL,checkMultiple,number);
	}

	for(int i=1;i<argc;i++)
		pthread_join(thr[i],NULL);

	free(thr);
	pthread_mutex_destroy(&mutex);
	printf("The number of numbers that are are multiple of 2 or 5 is %d\n",gVar);
	return 0;
}
