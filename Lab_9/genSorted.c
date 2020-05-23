#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define MAX 99

/*
Sa se scrie un program care genereaza pe 5 thread-uri distincte 1000 de numere intregi pe care le introduce intr-un vector global. 
Fiecare numar generat va fi introdus de thread-ul care l-a generat pe pozitia corecta in vector, astfel incat la orice moment vectorul sa fie sortat.
Threadul principal va afisa la fiecare 10 numere generate intreg continutul vectorului.
*/

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t c;

int vector[1000];
int size;

void addSorted(int x)
{
	int i=0;
	while(i<size && vector[i]<x)
		i++;
	size++;
	for(int j=size-1;j>i;j--)
		vector[j] = vector[j-1];
	vector[i] = x;
}


void* threadFunction(void* param)
{
	int randNr = rand()%MAX;
	while(size < 1000)
	{
		pthread_mutex_lock(&m2);
		addSorted(randNr);
		if(size%10 == 0)
		{
			printf("Size %d\n",size);
			pthread_mutex_unlock(&m1);
		}
		else
			pthread_mutex_unlock(&m2);
	}
	pthread_mutex_unlock(&m1);
	pthread_mutex_unlock(&m2);
	return NULL;
}


int main()
{

	srand(time(NULL));
	pthread_t thr[5];
	//pthread_cond_init(&c, NULL);
	for(int i=0;i<5;i++)
		pthread_create(&thr[i],NULL,threadFunction,NULL);
	
	while(size<=1000)
	{
		pthread_mutex_lock(&m1);
		for(int i=0;i<size;i++)
			printf("%d ", vector[i]);
		printf("\n\n");
		pthread_mutex_unlock(&m2);
	}
	pthread_mutex_unlock(&m1);
	pthread_mutex_unlock(&m2);
	
	for(int i=0;i<5;i++)
		pthread_join(thr[i],NULL);
	pthread_mutex_destroy(&m1);
	pthread_mutex_destroy(&m2);
	//pthread_cond_destroy(&c);
	return 0;
}
