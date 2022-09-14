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


int main(int argc, char **argv) {

  verifier(argc == 3, "il faut 3 parametre\n");

  FILE *input = fopen(argv[1], "r");
  FILE *output = fopen(argv[2], "w");

  verifier(input != NULL && output != NULL, "impossible d'ouvrire un des fichier\n");

  int read_size = 0;
  char buffer[1];

  do {
    read_size = fread(buffer, sizeof(char), 1, input);

    if (read_size == 0) continue;

    int ret = fwrite(buffer, sizeof(char), 1, output);
    verifier(ret == read_size, "Could not write\n");
  } while (read_size > 0);
  
  fclose(input);
  fclose(output);
 
  return EXIT_SUCCESS;
}
