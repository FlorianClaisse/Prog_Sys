#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void System(const char *arg) {
    pid_t pid = fork();

    if (pid == 0) {
        // Toujours ensemble
        execl("/bin/sh", "sh", "-c", arg, (char *) NULL);
        perror("/bin/sh");
        exit(EXIT_FAILURE);
    }
    // Toujours attendre
    int status;
    waitpid(pid, &status, 0);
}

int main(int argc, char const *argv[]) {

    System("sleep 1; ls");
    System("echo fin");

    return EXIT_SUCCESS;
}
