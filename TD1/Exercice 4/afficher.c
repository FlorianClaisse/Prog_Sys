#include <errno.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUFFIXE ".idx"

void verifier(int cond, char *s){
    if (!cond){
        perror(s);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]){
    verifier(argc == 3, "il faut deux paramètres.");

    // construire le chemin au fichier index
    int l = strlen(argv[1]) ;
    char idx_filename[l + strlen(SUFFIXE) + 1];

    strncpy(idx_filename, argv[1], l);
    strcpy(idx_filename + l, SUFFIXE);

    int input = open(argv[1], O_RDONLY);
    int index = open(idx_filename, O_RDONLY);
    off_t line = atoll(argv[2]);
    verifier(input >= 0 && index >= 0 && line >= 0, "Un de parametre est incorrecte\n");

    verifier(lseek(index, sizeof(off_t) * line, SEEK_SET) != -1, "Impossible de deplacer le curseur\n");

    off_t position;
    verifier(read(index, &position, sizeof(off_t)) != -1, "Impossible de lire la position de la ligne demandé\n");

    verifier(lseek(input, position * sizeof(char), SEEK_SET) != -1, "La ligne demandé n'existe pas dans le fichier\n");

    char character;
    while(read(input, &character, sizeof(char)) > 0 && character != '\n') { printf("%c", character); }
    printf("\n");

    close(input);
    close(index);

  return EXIT_SUCCESS;
}
