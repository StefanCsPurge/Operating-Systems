#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd = open("myfifo",O_RDONLY);
	int ca,ce,ci,co,cu;
	read(fd,&ca,sizeof(int));
	read(fd,&ce,sizeof(int));
	read(fd,&ci,sizeof(int));
	read(fd,&co,sizeof(int));
	read(fd,&cu,sizeof(int));
	unlink("myfifo");

	printf("'a' has frequency %d\n",ca);
	printf("'e' has frequency %d\n",ce);
	printf("'i' has frequency %d\n",ci);
	printf("'o' has frequency %d\n",co);
	printf("'u' has frequency %d\n",cu);

	return 0;
}

