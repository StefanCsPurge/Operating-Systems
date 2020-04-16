/*Scrieți programe părinte / copil in care copilul verifică dacă un număr e prim; 
 * părintele afișează numerele prime pană la N citit de la tastatură (wait + WEXITSTATUS). 
 * (this was my public question on piazza) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int prime(int x){
	if ( x<2 || (x>2 && x%2 == 0 ))
		return 0;
	for (int  d=3; d*d<=x ; d+=2)
		if (x%d==0)
			return 0;
	return 1;
}

int main(){
	int n, status, i, f, exitStatus;
	int *e;
	printf("Enter n: ");
	scanf("%d",&n);
	e=(int*)malloc((n+1)*sizeof(int));
	for (i=0;i<=n;i++){
		f=fork();
		if (f<0){
			perror("Unable to create the child process");
			exit(1);
		}	
		if (f==0){
			free(e);
			exit(prime(i));
		}
		//printf("%d\n",f);
		e[i]=f;
	}
	for(i=0;i<=n;i++){
		waitpid(e[i],&status,0);
		exitStatus=WEXITSTATUS(status);
		if(exitStatus == 1){
			printf("%d ",i);
			fflush(stdout);
		}
	}
	printf("\n");
	free(e);
	return 0;
}
