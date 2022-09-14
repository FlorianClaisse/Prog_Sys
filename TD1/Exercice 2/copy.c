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

  verifier(argc == 4, "il faut 4 parametre\n");

  int input = open(argv[1], O_RDONLY);
  int output = open(argv[2], O_WRONLY| O_CREAT | O_SYNC, 0600);
  int size = atoi(argv[3]);

  verifier(input >= 0 && output >= 0 && size > 0, "impossible d'ouvrire un des fichier\n");

  int read_size = 0;
  char *buffer = malloc(sizeof(char) * size);

  do {
    read_size = read(input, buffer, size);

    if (read_size == 0) continue;

    int ret = write(output, buffer, read_size);
    verifier(ret == read_size, "Could not write\n");
  } while (read_size > 0);
  
  free(buffer);
  close(input);
  close(output);
 
  return EXIT_SUCCESS;
}
