#include <errno.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUFFIXE ".idx"
#define BUF_SIZE 2048


void verifier(int cond, char *s){
    if (!cond){
        perror(s);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]){
    verifier(argc == 2, "il faut un paramètre.");

    // construire le chemin au fichier index
    int l = strlen(argv[1]) ;
    char idx_filename[l + strlen(SUFFIXE) + 1];
    strncpy(idx_filename, argv[1], l);
    strcpy(idx_filename + l, SUFFIXE);

    int input = open(argv[1], O_RDONLY);
    int fileIndex = open(idx_filename, O_WRONLY | O_CREAT, 0666);
    verifier(input >= 0 && fileIndex >= 0, "Impossible d'ouvrir l'un des fichier\n");

    char readValue;
    off_t currentPos = 0;
    verifier(write(fileIndex, &currentPos, sizeof(off_t)) != -1, "Impossible d'ecrire dans le fichier\n");
    
    while(read(input, &readValue, sizeof(char)) > 0) {
        if (readValue != '\n') continue;
        currentPos = lseek(input, 0, SEEK_CUR);
        verifier(write(fileIndex, &currentPos, sizeof(off_t)) != -1, "Impossible d'ecrire dans le fichier\n");
    }

    close(input);
    close(fileIndex);
    
    return EXIT_SUCCESS;
}
