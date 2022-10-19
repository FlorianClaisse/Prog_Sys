#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>

struct sigaction new, old;

void handler(int sig) {
    if (sig == SIGINT) {
        printf("ctrl-c\n");
        sigaction(sig, &old, &new);
    }
}

int main(int argc, char const *argv[]) {

    new.sa_flags = 0;
    sigemptyset(&new.sa_mask);
    new.sa_handler = handler;
    sigaction(SIGINT, &new, &old);

    while(1);
    
    return EXIT_SUCCESS;
}

