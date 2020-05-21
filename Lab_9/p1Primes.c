#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

/*A) Sa se afiseze cate numere prime sunt in intervalul 1-2,000,000,000.
            - in prima varianta se implementeaza iterativ
            - se masoara timpul de executie
            - se incearca cu 2, 4, 8 threaduri, fiecare prelucrand un subinterval, si se va determina care varianta este mai rapida */

int nr=0; // total number of primes

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct
{
	int start,end;
	int count;
}Interval;

int prime(int x)
{
	if(x<2 || (x>2 && x%2==0))
		return 0;
	for(int d=3;d*d<=x;d+=2)
		if(x%d==0)
			return 0;
	return 1;
}

void normalCheck()
{
	nr=0;
	clock_t begin = clock();

	for(int i=1;i<20000000;i++)
		if(prime(i))
			nr++;
	printf("%d\n",nr);
	
	clock_t end = clock();

	double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
	printf("The time is %f\n",time_spent);
	// The iterative normal implementation takes 5.003442 s
}

void* checkInterval(void *param)
{
	Interval *intv = (Interval*)param;
	intv->count=0;

	for(int i = intv->start; i < intv->end; i++)
		if(prime(i))
			intv->count++;
	return NULL;
}


void threadCheck(int n)
{
	nr=0;
	pthread_t threads[n];
	int returnVal;
	Interval intervals[n];

	for(int i=0;i<n;i++)
	{
		intervals[i].start = (200000000/n)* i;
		intervals[i].end = (200000000/n) * (i+1);

		returnVal = pthread_create(&threads[i],NULL,checkInterval,&intervals[i]);

		if(returnVal)
		{
			printf("Error - couldn't create thread!\n");
			exit(1);
		}
	}

	int total=0;
	for(int i=0;i<n;i++)
	{
		pthread_join(threads[i],NULL);
		total += intervals[i].count;
	}
	nr = total;

	printf("%d primes\n",nr);
}



int main()
{
	printf("Insert number of threads: ");
	int n;
	scanf("%d",&n);

	clock_t begin = clock();
	
	threadCheck(n);

	clock_t end = clock();
	double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
	printf("The time is %f\n",time_spent);	
	
	
	return 0;
}
