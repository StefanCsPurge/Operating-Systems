/* Scrieți un program care așteaptă indefinit și nu poate fi omor�t cu SIGTERM. Mai poate fi oprit?
*/
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void f()
{
	// this boi refuses
	printf("I wont't stop!\n");
}


int main()
{
	signal(SIGTERM, f);
	while(1) sleep(1);
	// this can be stopped by SIGKILL or SIGINT
	// so it can be killed with kill -9 <PID> (the ultimate killer), or Ctrl-C
	return 0;
}
