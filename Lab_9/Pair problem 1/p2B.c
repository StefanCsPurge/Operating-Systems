#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

int main()
{
	int fd;
	if((fd = open("myfifo",O_RDONLY)) < 0){
		perror("Error on open fifo");
		exit(5);
	}

	int sum;
	if(read(fd,&sum,sizeof(int)) < 0){
		perror("Error on read sum from fifo");
		exit(5);
	}
	printf("The number received is %d\n",sum);

	unlink("myfifo");
	return 0;
}
