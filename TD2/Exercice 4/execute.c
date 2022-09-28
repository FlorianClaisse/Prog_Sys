#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int Execute(int argc, char *command[]) {
    int pid = fork();

    if (pid == 0) {

        execvp(command[1], command + 1);
        fprintf(stderr, "%s", command[1]);
        exit(EXIT_FAILURE);
    }

    int status;
    waitpid(pid, &status, 0);

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }

    return WTERMSIG(status) + 128;
}

int main(int argc, char const *argv[]) {

    printf("*** execution\n");
    int status = Execute(argc, argv);
    printf("*** code de retour : %d\n", status);
    
    return EXIT_SUCCESS;
}
