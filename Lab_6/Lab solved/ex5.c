/// Inițializați un vector cu numerele de la 1 la N (citit de la tastatură). Programul inițial trebuie să producă un proces copil și fiecare să calculeze suma a jumătate din numere (ex. părintele să adune numerele pare, copilul cele impare) adunand la o variabilă globală comună. Explicați rezultatul.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int globalSum = 9;

int main()
{
	int a[111],n;
	printf("n = ");
	scanf("%d",&n);

	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);

	int c = fork();
	if(!c) // we execute the child if c is 0
	{
		for(int i=0;i<n;i++)
			if(a[i] % 2 == 0)
				globalSum += a[i];
		printf("The sum after child computation is %d\n",globalSum);
		exit(0);
	}
	wait(0);
	for(int i=0;i<n;i++)
		if(a[i]%2)
			globalSum += a[i];
	printf("The sum after all the computations: %d \n",globalSum);
	// this sum won't be the expected one because the memory is not shared between the parent and the child
	// this can be fixed with pipes 
	return 0;
}
