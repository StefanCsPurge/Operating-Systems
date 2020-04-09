///Analizați și explicați efectul secvenței

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int i, j, k;
    i = fork();
    /*2 processes from now on
     * i = PID for the parent process, 
     * i=0 for the child process 
     * */

    if ((j = fork())) { 
	// j is 0 for child and PID for parent (non-zero), so only the parent process executes the if
	// there are 4 processes now (previous parent and child both forked)
        k = fork(); // 2 more processes are created here(1 for each previous parent) -> 6
    }
    /*In the end we have a total of 6 processes:
     * 1 original process (the father of all)
     * 3 children from the original one
     * 2 children of the child of original one 
     * */
    printf("%d %d %d %d %d\n", i, j, k, getpid(), getppid());
    return 0;
}
