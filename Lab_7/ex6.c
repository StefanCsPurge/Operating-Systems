/*Rescrieți soluția problemei 3 folosind pipe-ul cu nume (FIFO) /tmp/pb6 (mkfifo, fopen, unlink).*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


int main()
{
	int a, b;
	char* path = "/tmp/pb6";
	mkfifo(path, 0600);
	FILE *handle;

	if(fork() == 0)
	{
		handle = fopen(path, "r");
		fread(&a, 1, sizeof(int), handle);
		fread(&b, 1, sizeof(int), handle);

		fclose(handle);

		int sum = a+b;
		
		handle = fopen(path, "w");
		fwrite(&sum, 1, sizeof(int), handle);

		fclose(handle);
		printf("The sum (in child) is %d\n",sum);
		exit(0);
	}


	handle = fopen(path, "w");
	printf("Enter a and b: ");
        scanf("%d",&a);
        scanf("%d",&b);

	fwrite(&a, 1, sizeof(int), handle);
	fwrite(&b, 1, sizeof(int), handle);

	fclose(handle);
	unlink(path);
	wait(0);

	handle = fopen(path, "r");
	int sum = 0;
	fread(&sum, 1, sizeof(int), handle);
	printf("The sum (in parent) is %d\n", sum);
	fclose(handle);
	unlink(path);
	return 0;
}

