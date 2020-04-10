/*
    Scrieți un program care fork()-uie un proces copil, citește de la tastatură două numere și le trimite către copil. Copilul primește numerele, calculează și afișează suma (fork, pipe, write, read).
    Modificați programul astfel �nc�t copilul să returneze suma către părinte și acesta din urmă să facă afișarea.
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	int p2c[2],c2p[2],a,b;
	pipe(p2c);
	pipe(c2p);

	if(fork() == 0)
	{
		close(p2c[1]);
		close(c2p[0]);

		read(p2c[0],&a,sizeof(int));
		read(p2c[0],&b,sizeof(int));
		close(p2c[0]);

		int sum = a+b;
		printf("The sum (in child) is %d \n",sum);
		
		write(c2p[1],&sum,sizeof(int));
		close(c2p[1]);
		exit(0);
	}

	close(p2c[0]);
	close(c2p[1]);

	printf("Enter a and b: ");
	scanf("%d",&a);
	scanf("%d",&b);
	
	write(p2c[1],&a,sizeof(int));
	write(p2c[1],&b,sizeof(int));
	
	close(p2c[1]);

	wait(0);

	int sum=0;
	read(c2p[0],&sum,sizeof(int));
	close(c2p[0]);

	printf("The sum (in parent) is %d \n",sum);
	return 0;
}
