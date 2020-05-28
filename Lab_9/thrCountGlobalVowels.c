#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int vowels = 0;

void* thrFunction(void *param)
{
	char* word = (char*)param;
	int n = strlen(word);
	for(int i=0;i<n;i++)
		if(strchr("aeiou",word[i]))
		{
			pthread_mutex_lock(&m);
			vowels++;
			pthread_mutex_unlock(&m);
		}
	free(param);
	return NULL;
}

int main()
{
	int N;
	printf("N = ");
	scanf("%d",&N);
	pthread_t thr[N];
	for(int i=0;i<N;i++)
	{
		char* word = malloc(101*sizeof(char));
		scanf("%s",word);
		pthread_create(&thr[i],NULL,thrFunction,word);
	}

	for(int i=0;i<N;i++)
		pthread_join(thr[i],NULL);
	pthread_mutex_destroy(&m);

	printf("The total number of vowels is %d\n",vowels);
	return 0;
}
