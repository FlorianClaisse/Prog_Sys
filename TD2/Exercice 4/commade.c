#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int command(int argc, const char *argv[]) {

    long long size = 2 + (argc - 1) + strlen("sh -c");
    for (int i = 1; i < argc; i++) size += strlen(argv[i]);

    char *cmd = malloc(sizeof(char*) * size); 
    strcat(cmd, "sh -c ");
    strcat(cmd, "\"");
    for (int i = 1; i < argc; i++) {
        strcat(cmd, argv[i]);
        strcat(cmd, " ");
    }
    strcat(cmd, "\"");
    int stat = execl("/bin/sh", "sh", "-c", cmd, (char *) NULL);

    
    return stat;
}

int main(int argc, char const *argv[]) {

    if (argc < 2) perror("Il faut au minimum un parametre\n");

    pid_t fils = fork();

    if (fils == -1) perror("Erreur lors de la creation du processus fils\n");
    else if (fils == 0) {
        // system call
        int stat = command(argc, argv);
        return stat;
    }

    int status;
    waitpid(fils, &status, 0);
    printf("Fin du processus\n");
    
    return EXIT_SUCCESS;
}
