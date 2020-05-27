#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Program that creates a thread that extracts the char at position nr from a file, for every file-nr pair
typedef struct
{
	char fileName[55];
	int x;
}ma_pair;


void* threadFct(void *param)
{
	ma_pair p = *(ma_pair*)param;
	free(param);
	char c;
	int cnt = 0;
	FILE *f = fopen(p.fileName,"r");
	while((c = fgetc(f)) != EOF && cnt<=p.x)
	{
		if(cnt == p.x)
		{
			printf("Found '%c' on position %d in file %s\n",c,p.x,p.fileName);
			return NULL;
		}
		cnt++;
	}
	printf("Number is too big ffs\n");
	return NULL;
}

int main()
{
	int n;
	printf("n=");
	scanf("%d",&n);
	pthread_t thr[n];
	printf("Insert file - number pairs\n");
	for(int i=0;i<n;i++)
	{
		//printf("Pair %d\n",i);
		ma_pair* p = malloc(sizeof(ma_pair));
		scanf("%s",p->fileName);
		scanf("%d",&p->x);
		pthread_create(&thr[i],NULL,threadFct,p);
	}

	for(int i=0;i<n;i++)
		pthread_join(thr[i],NULL);

	return 0;
}
