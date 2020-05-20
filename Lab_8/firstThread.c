
// COMPILE WITH
// gcc -pthread -Wall source.c -o output

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THR_COUNT 4

void* thread_function(void *param)
{
	int nr = *(int*)param;

	printf("I am thread %lu with the parameter %d\n", (ulong)pthread_self(), nr);
	return 0;
}


int main()
{
	int i=0;
	pthread_t thr[THR_COUNT];
	int thr_param[THR_COUNT];

	//create threads
	for(i=0;i<THR_COUNT;i++)
	{
		//prepare the parameters
		thr_param[i] = i;

		pthread_create(&thr[i],NULL,thread_function,&thr_param[i]);
	}
	//wait for threads to terminate
	for(i=0;i<THR_COUNT;i++)
		pthread_join(thr[i],NULL);

	printf("Done\n");
	return 0;
}
