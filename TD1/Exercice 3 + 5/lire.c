#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

void verifier(int cond, char *s){
    if (!cond){
        perror(s);
        exit(EXIT_FAILURE);
    }
}

// Function for exercice 1.5
void redirectionErreur(void) {
    int file = open("ERREURS-LIRE.log", O_WRONLY | O_CREAT, 0666);
    verifier(file >= 0, "Impossible d'ouvrir le fichier\n");
    dup2(file, STDERR_FILENO);
    // Ligne pour tester
    char buff[11] = "impossible\0";
    write(STDERR_FILENO, buff, sizeof(char) * 11);
}


int main(int argc, char const *argv[]) {
    verifier(argc == 3, "Il faut 2 parametre, fichier et position\n");
    redirectionErreur();

    int position = atoi(argv[2]);
    int file = open(argv[1], O_RDONLY);
    off_t readValue;
    
    verifier(position >= 0 && file >= 0, "L'un des parametre du programme est incorrecte\n");

    off_t check = lseek(file, sizeof(off_t) * position, SEEK_SET);
    verifier(check == sizeof(off_t) * position, "Impossible de deplacer le curseur\n");

    ssize_t returnValue = read(file, &readValue, sizeof(off_t));
    verifier(returnValue == sizeof(off_t), "Impossible de lire dans le fichier\n");

    printf("value = %lld\n", readValue);

    verifier(close(file) == 0, "Impossible de fermer le fichier\n");

    return EXIT_SUCCESS;
}
