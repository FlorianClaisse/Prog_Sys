#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {

    if (argc != 2) perror("Il faut 1 parametre");

    int child_numbers = atoi(argv[1]);
    pid_t pere = getpid();

    for (int i = 0; i < child_numbers; i++) {
        pid_t pid = fork();
        if (pid == 0) { 
            printf("Je suis le fils de %d numero %d\n", pere, i); 
            return EXIT_SUCCESS;
        }
    }

    int status;
    for (int i = 0; i < child_numbers; i++) {
        waitpid(-1, &status, 0);
    }
    printf("Je suis le pere est tous est fini\n");
    
    return EXIT_SUCCESS;
}
