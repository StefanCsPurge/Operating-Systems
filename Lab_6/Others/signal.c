#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


int children[3];
void hp(int sgn) {
    int i;
    if(sgn == SIGINT) {
        printf("%d: sending SIGUSR2\n",getpid());
        for(i=0; i<3; i++) {
            kill(children[i], SIGTERM);
        }
    }
    else if(sgn == SIGTERM) {
        printf("%d: sending SIGKILL\n",getpid());
        for(i=0; i<3; i++) {
            kill(children[i], SIGKILL);
        }
    }
}
void hc(int sgn) {
    if(sgn == SIGTERM) {
        printf("%d: Received SIGUSR2\n",getpid());
    }
}

int main(int argc, char** argv) {
    int i;
    signal(SIGINT, hp);
    signal(SIGTERM, hp);
    for(i=0; i<3; i++) {
        children[i] = fork();
        if(children[i] == 0) {
            signal(SIGTERM, hc);
            while(1);
            exit(0);
        }
    }
    wait(0);
    wait(0);
    wait(0);
    return 0;
}
