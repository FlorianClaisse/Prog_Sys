#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {

    pid_t fils = fork();

    if (fils == -1) { perror("Error lors de la creation du prcessus\n"); }
    else if (fils == 0) { 
        int stat = execl("/bin/sh", "sh", "-c", "ls", (char *) NULL);
        return stat;
    }

    int status;
    waitpid(fils, &status, 0);
    return EXIT_SUCCESS;
    
    return EXIT_SUCCESS;
}
