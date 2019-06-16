/**
 * SO, 2017
 * Lab #2, Operatii I/O simple
 *
 * Task #3, Linux
 *
 * cat/cp applications
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "utils.h"

#define BUFSIZE        32

int main(int argc, char **argv) {
    int fd_src, fd_dst, rc, bytesRead;
    char buffer[BUFSIZE];

    if (argc < 2 || argc > 3) {
        printf("Usage:\n\t%s source_file [destination_file]\n",
               argv[0]);
        return 0;
    }

    /* TODO 1 - open source file for reading */
    int file_descriptor = open(argv[1], O_RDONLY);
    DIE(file_descriptor < 0, "open file");

    if (argc == 3) {
        /* TODO 2 - redirect stdout to destination file */
        int fd_write = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, 0600);
        DIE(fd_write < 0, "error open file!");
        dup2(fd_write, STDOUT_FILENO);
    }

    fprintf(stderr, "%d\n", STDOUT_FILENO);
    int f = STDOUT_FILENO;
    fprintf(stderr, "%d\n", f);

    /* TODO 1 - read from file and print to stdout
     * use _only_ read and write functions
     */

    int len_read;
    while (1) {
        len_read = (int) read(file_descriptor, buffer, BUFSIZE);
        if (len_read == 0) {
            break;
        }

        write(STDOUT_FILENO, buffer, (size_t) len_read);
    }

    /* TODO 1 - close file */
    DIE(close(file_descriptor) != 0, "error close file!");

    return 0;
}
