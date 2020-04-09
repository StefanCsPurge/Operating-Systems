/// Citiți o comandă de la tastatură și rulați-o cu fork + exec.

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// I'll read the command from the arguments
int main(int argc, char** argv)
{
	if(!fork())
	{
		execvp(argv[1],argv+1);
		exit(0);
	}
	wait(0);
	return 0;
}
