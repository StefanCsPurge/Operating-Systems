#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

/*
Sa se scrie un program care genereaza pe 5 thread-uri distincte 1000 de numere intregi
pe care le introduce intr-un vector global.

Fiecare numar generat va fi introdus de thread-ul care l-a generat pe pozitia corecta in vector,
astfel incat la orice moment vectorul sa fie sortat.

Programul va creea alte 3 thread-uri care extrag din vector numarul cel mai apropiat
de media aritmetica a numerelor prezente in vector.
Extragerea va avea loc la fiecare 10 numere generate.

Threadul principal va afisa la fiecare 10 numere generate intreg continutul vectorului.
*/

#define MAX 99

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m3 = PTHREAD_MUTEX_INITIALIZER;

int vector[1000];
int size;
int sum;

void addSorted(int x)
{
    int i=0;
    while(i<size && vector[i]<x)
        i++;
    size++;
    for(int j=size-1; j>i; j--)
        vector[j] = vector[j-1];
    vector[i] = x;
}

int getClosestToAverage()
{
    int avg = sum/size, foundVal=vector[0], mini = abs(vector[0]-avg), i=1;
    for(;i<size;i++)
	    if(abs(vector[i]-avg)< mini)
	    {
		    mini = abs(vector[i]-avg);
		    foundVal = vector[i];
	    }
    return foundVal;
}


void* avgThread(void* param)
{					// the 3 threads that get the closest element to the average
    while(1)
    {
        pthread_mutex_lock(&m3);
        if(size<10) {
            pthread_mutex_unlock(&m3);
            continue;
        }
	if(size>1000)
	{
		pthread_mutex_unlock(&m2);
		pthread_mutex_unlock(&m3);
		break;
	}
        if(size==1000)
        {
            printf("Size %d, found value %d closest to avg %d\n\n",size,getClosestToAverage(),sum/size);
	    size+=1;
	    pthread_mutex_unlock(&m3);
	    pthread_mutex_unlock(&m2);
            break;
        }
        printf("Size %d, found value %d closest to avg %d\n\n",size,getClosestToAverage(),sum/size);
        pthread_mutex_unlock(&m2);
    }
    return NULL;
}

void* threadFunction(void* param)
{	 				// the 5 threads that add the elements to the vector
    srand(pthread_self()-time(NULL));     
    int randNr = rand()%MAX;
    while(1)
    {
        pthread_mutex_lock(&m2);
        if(size>1000)
        {
            pthread_mutex_unlock(&m2);
            break;
        }
        addSorted(randNr);
        sum += randNr;
        if(size%10 == 0)
            pthread_mutex_unlock(&m1);
        else
            pthread_mutex_unlock(&m2);
    }
    return NULL;
}

int main()
{
    pthread_t thr[5],avgThr[3];
    for(int i=0; i<5; i++)
        pthread_create(&thr[i],NULL,threadFunction,NULL);
    pthread_mutex_lock(&m3);
    for(int i=0; i<3; i++)
        pthread_create(&avgThr[i],NULL,avgThread,NULL);
    while(1)                          
    {
        pthread_mutex_lock(&m1);
        if(size<10) {
            pthread_mutex_unlock(&m1);
            continue;
        }
        printf("Size %d\n",size);     // we print the elements at each 10 elements generated
        if(size == 1000)
        {
            for(int i=0; i<size; i++)
                printf("%d ", vector[i]);
            printf("\n");
            pthread_mutex_unlock(&m3);
            break;
        }
        for(int i=0; i<size; i++)
            printf("%d ",vector[i]);
        printf("\n");
        pthread_mutex_unlock(&m3);  // let the 3 threads compute the element closest to the average
    }

    for(int i=0; i<5; i++)
        pthread_join(thr[i],NULL);
    for(int i=0; i<3; i++)
        pthread_join(avgThr[i],NULL);
    pthread_mutex_destroy(&m1);
    pthread_mutex_destroy(&m2);
    pthread_mutex_destroy(&m3);
    return 0;
}
