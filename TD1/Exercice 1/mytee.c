#include <errno.h>
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void verifier(int cond, char *s){
  if (!cond){
    perror(s);
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char const *argv[]) {
    verifier(argc == 2, "il faut deux parametre\n");

    int read_size = 0;
    char buffer[BUFSIZ + 1];

    int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0600);
    verifier(fd >= 0, "could not open file");

    do {
        read_size = read(STDIN_FILENO, buffer, BUFSIZ);
        
        if (read_size == 0) { continue; }

        buffer[read_size] = '\0';
        printf("%s", buffer);

        int ret = write(fd, buffer, read_size);
        verifier(ret == read_size, "could not write\n");
    } while (read_size > 0);

    close(fd);
    
    return EXIT_SUCCESS;
}
