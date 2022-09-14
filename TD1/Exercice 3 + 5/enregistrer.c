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

int main(int argc, char const *argv[]) {

    verifier(argc == 4, "Il faut 3 parametre fichier, position, valeur\n");

    int file = open(argv[1], O_WRONLY| O_CREAT, 0600);
    int position = atoi(argv[2]);
    off_t value = atoll(argv[3]);

    verifier(file > 0 && position >= 0, "Une des valeur passé en parametre n'est pas correcte\n");

    off_t check = lseek(file, sizeof(off_t) * position, SEEK_SET);
    verifier(check == sizeof(off_t) * position, "Impossible de deplacer le curseur\n");

    ssize_t returnValue = write(file, &value, sizeof(off_t));
    verifier(returnValue == sizeof(off_t), "L'ecriture n'a pas fonctionné");

    check = close(file);
    verifier(check == 0, "Impossible de fermer le fichier\n");
    
    return EXIT_SUCCESS;
}
