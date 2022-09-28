#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fnmatch.h>

int Execute(char *command[]) {
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

    DIR *d = opendir(".");
    if (d == NULL) fprintf(stderr, "Probleme lors de l'ouverture du dossier courant\n");

    struct dirent *e;
    char *pattern = argv[argc - 1];

    while ((e = readdir(d)) != NULL) {
        if (fnmatch(pattern, e->d_name, FNM_PATHNAME) == 0) {
            argv[argc - 1] = e->d_name;
            Execute(argv);
        }
    }

    
    
    return EXIT_SUCCESS;
}
