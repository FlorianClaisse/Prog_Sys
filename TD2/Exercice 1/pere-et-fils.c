#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {

    pid_t pid;
    pid_t pere = getpid();

    pid = fork();
    if (pid == -1) {
        perror("Error creating child process\n");
    } else if (pid == 0) {
        printf("je m'appelle %d, et je suis le fils de %d\n", getpid(), pere);
        return EXIT_SUCCESS;
    }

    int status;
    waitpid(pid, &status,0);
    printf("je m'appelle %d et je suis le père de %d\n", pere, pid);

    return EXIT_SUCCESS;
}
