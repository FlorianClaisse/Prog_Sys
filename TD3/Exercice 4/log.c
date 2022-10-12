#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

enum { R, W };


int main (int argc, const char* argv[]) {

    if (argc < 3) {
        fprintf(stderr, "./log <file> <command> [<args>]");
        exit(EXIT_FAILURE);
    }
    int pipefd[2];
    pipe(pipefd);
    pid_t pid = fork();

    if (pid == 0) {
        close(pipefd[R]);
        dup2(pipefd[W], STDOUT_FILENO);
        close(pipefd[W]);
        execvp(argv[2], argv + 2);
    }

    close(pipefd[W]);
    dup2(pipefd[R], STDIN_FILENO);

    int read_size = 0;
    char buffer[BUFSIZ + 1];

    int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0666);

    do {
        read_size = read(pipefd[R] /*STDIN_FILENO*/, buffer, BUFSIZ);
        
        if (read_size == 0) { continue; }

        buffer[read_size] = '\0';
        printf("%s", buffer);

        int ret = write(fd, buffer, read_size);
        
    } while (read_size > 0);

    return EXIT_SUCCESS;
}