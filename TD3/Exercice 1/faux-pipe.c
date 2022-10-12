#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define FILENAME "tmpfile.tmp"

int main(int argc, char const *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "Il faut au minimum 2 parametre\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    int status;
    int tmpfile;
    if (!pid) {
        tmpfile = open(FILENAME, O_CREAT | O_TRUNC | O_RDWR, 0666);
        dup2(tmpfile, STDOUT_FILENO);
        execl("/bin/sh", "sh", "-c", argv[1], NULL);
    }

    waitpid(pid, &status, 0);
    int file2 = open(FILENAME, O_RDONLY, 0666);

    dup2(file2, STDIN_FILENO);
    execvp(argv[2], argv + 2);
    
    return EXIT_SUCCESS;
}
