/// Scrieți programe părinte / copil in care copilul verifică dacă un număr e prim; părintele afișează numerele prime pană la N citit de la tastatură

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int prime(int x)
{
    if(x<2||(x>2 && x%2==0))
        return 0;
    for(int d=3; d*d<=x; d+=2)
        if(x%d==0)
            return 0;
    return 1;
}

int main(int argc, char** argv)
{
	int n,status,i;
	printf("Enter N: ");
	scanf("%d",&n);
	for(i=0;i<=n;i++){
		if(fork() == 0){
			if(prime(i))
				exit(0);
			exit(1);
		}
		wait(&status);
		if(WEXITSTATUS(status) == 0)
			printf("%d\n",i);
	}
	return 0;
}

