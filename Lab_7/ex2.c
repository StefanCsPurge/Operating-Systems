//Scrieți un program care afișează data + ora curentă c�nd primește semnalul HUP
#include <stdio.h>
#include <time.h>
#include <signal.h>

void showCurrentTime()
{
	time_t curtime;
	time(&curtime);
	printf("Current time = %s",ctime(&curtime));
}

int main()
{
	//showCurrentTime();
	signal(SIGHUP,showCurrentTime);
	while(1);
	return 0;
}
