#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int argc, char const *argv[]) {

    int i, fd;
    if (argc != 2) {
        fprintf(stderr, "Usage: ecrire <position_depart>\n");
        exit(1);
    }

    fd = open("fich", O_WRONLY | O_CREAT, 0666);

    for (i = atoi(argv[1]); i < 10; i += 2) {
        lseek(fd, i * sizeof(int), SEEK_SET);
        write(fd, &i, sizeof(int));
        sleep(1);
    }

    close(fd);

    return EXIT_SUCCESS;
}
