#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

enum { R, W };
int pipefd[2];

int main(int argc, const char* argv[]) {

    if (argc < 3) {
        fprintf(stderr, "Il faut au minimum 2 parametre\n");
        exit(EXIT_FAILURE);
    }

    pipe(pipefd);
    pid_t pid = fork();
    if (pid == 0) {
        close(pipefd[R]);
        dup2(pipefd[W], STDOUT_FILENO);
        close(pipefd[W]);
        execl("/bin/sh", "sh", "-c", argv[1], NULL);
    }

    pid_t pid2 = fork();
    if (pid == 0) {
        close(pipefd[W]);
        dup2(pipefd[R], STDIN_FILENO);
        close(pipefd[R]);
        execvp(argv[2], argv + 2);
    }
    
    close(pipefd[R]);
    close(pipefd[W]);

    int status, status2;
    waitpid(pid, &status, 0);
    waitpid(pid2, &status2, 0);

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }

    return WEXITSTATUS(status2);
}