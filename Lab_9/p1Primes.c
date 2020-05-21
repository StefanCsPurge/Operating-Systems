#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

/*A) Sa se afiseze cate numere prime sunt in intervalul 1-2,000,000,000.
 *  - in prima varianta se implementeaza iterativ
 *  - se masoara timpul de executie
 *  - se incearca cu 2, 4, 8 threaduri, fiecare prelucrand un subinterval, si se va determina care varianta este mai rapida */

#define LIMIT 1000000

int nr=0; // total number of primes
int currentNumber=0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;

typedef struct
{
    int start,end;
    int count;
} Interval;

int prime(int x)
{
    if(x<2 || (x>2 && x%2==0))
        return 0;
    for(int d=3; d*d<=x; d+=2)
        if(x%d==0)
            return 0;
    return 1;
}


void normalCheck()
{
    nr=0;
    clock_t begin = clock();

    for(int i=1; i<LIMIT; i++)
        if(prime(i))
            nr++;
    printf("%d\n",nr);

    clock_t end = clock();

    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("The time is %f\n",time_spent);
    /// The iterative normal implementation takes 5.003442 s

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


void threadCheck_subintervals(int n)
{
    nr=0;
    pthread_t threads[n];
    int returnVal;
    Interval intervals[n];

    for(int i=0; i<n; i++)
    {
        intervals[i].start = (LIMIT/n)* i;
        intervals[i].end = (LIMIT/n) * (i+1);

        returnVal = pthread_create(&threads[i],NULL,checkInterval,&intervals[i]);

        if(returnVal)
        {
            printf("Error - couldn't create thread!\n");
            exit(1);
        }
    }

    int total=0;
    for(int i=0; i<n; i++)
    {
        pthread_join(threads[i],NULL);
        total += intervals[i].count;
    }
    nr = total;

    printf("%d primes\n",nr);
}

void* checkCurrentNr()
{
    int aux;
    while(currentNumber < LIMIT)
    {
        pthread_mutex_lock(&mutex);
        aux = currentNumber;
        currentNumber ++;
        pthread_mutex_unlock(&mutex);

        if(prime(aux) == 1)
        {
            pthread_mutex_lock(&m2);
            nr ++;
            pthread_mutex_unlock(&m2);
        }
    }
    return NULL;
}

void threadCheck_noSync(int n)
{
    nr=0;
    pthread_t thr[n];
    int returnVal;
    for(int i=0; i<n; i++)
    {
        returnVal = pthread_create(&thr[i],NULL,checkCurrentNr,NULL);
        if(returnVal)
        {
            printf("Error - thread couldn't be created!");
            exit(1);
        }
    }
    for(int i=0; i<n; i++)
        pthread_join(thr[i],NULL);
    printf("\n%d primes\n",nr);
}


int main()
{
    normalCheck();

    int n=0;
    double time_spent = 0.0;
    clock_t begin,end;


    printf("\nInsert number of threads: ");
    scanf("%d",&n);

    begin = clock();

    threadCheck_subintervals(n);

    end = clock();
    time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("The time is %f\n",time_spent);


    printf("\nInsert number of threads (better version): ");
    scanf("%d",&n);

    begin = clock();

    threadCheck_noSync(n);

    end = clock();
    time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("The time is %f\n",time_spent);

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&m2);
    return 0;
}
