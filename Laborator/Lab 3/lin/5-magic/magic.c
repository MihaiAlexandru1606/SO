/**
  * SO, 2017
  * Lab #3
  *
  * Task #5, lin
  *
  * Use your magic to make this program print 'Hello World'
  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>


int main(void) {
    if (fork()) {
        printf(" Hello ");
    } else {
        printf(" World \n");
    }

    return 0;
}
