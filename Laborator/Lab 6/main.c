//
// Created by mihai on 17.04.2019.
//
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    int fd = open("file.txt", O_RDWR);
    /*char var[7] = {'1', '2', '3', '4', '5', '6', '7'};
    for (int i = 0; i < getpagesize() * 5; i++)
        write(fd, &var[i / getpagesize()], 1);
*/
    /*char *src = mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_SHARED,
                     fd, 0);


    int j = lseek(fd, 0, SEEK_END);
    char *src1 = mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_SHARED ,
                      fd, 0);

    for (int i = 0; i < 40; i++) {
        printf("SRC 1 %d, val : %c \n", i, src[i]);
        printf("SRC 2 %d, val : %c \n", i, src1[i]);
    }
    */
    char *src = mmap(NULL, getpagesize() * 1000, PROT_READ, MAP_SHARED, fd,  2* getpagesize());
    for (int i = 0; i < getpagesize() * 2; ++i) {
        printf("%c\n", src[i]);
    }
    /*char *src = malloc(100 * sizeof(char));
    char *s = mmap(src, 10000, PROT_READ, MAP_SHARED, fd, 0);

    printf("%p %p\n", src, s);
    for (int i = 0; i < 10; i++){
        printf("%c  %c\n", src[i], s[i]);
    }*/
    return 0;
}
