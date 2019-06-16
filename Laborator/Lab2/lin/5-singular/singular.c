/**
 * SO, 2017
 * Lab #2, Operatii I/O simple
 *
 * Task #5, Linux
 *
 * Locking a file
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>    /* flock */
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>    /* errno */

#include "utils.h"
#include <assert.h>

#define LOCK_FILE    "/tmp/my_lock_file"

static int fdlock = -1;


static void do_stuff(void) {
    sleep(10);
}


static void check_lock(void) {
    int rc;

    /* TODO - open LOCK_FILE file */
    if (fdlock < 0)
        fdlock = open(LOCK_FILE, O_CREAT | O_RDWR, 0644);
    assert(fdlock >= 0);

    /* TODO - lock the file using flock
     * - flock must not block in any case !
     *
     * - in case of error - print a message showing
     *   there is another instance running and exit
     */

    while (flock(fdlock, LOCK_EX | LOCK_NB) == -1){
    }
    printf("\nGot Lock\n\n");
    /**
    if (flock(fdlock, LOCK_EX | LOCK_NB) == -1) {
        if (errno == EWOULDBLOCK) {
            printf("Blocat!!");
        } else {
            printf("error");
        }
    } else {
        printf("\nGot Lock\n\n");
    }*/
}

static void clean_up(void) {
    int rc;

    /* TODO - unlock file, close file and delete it */
    assert(flock(fdlock, LOCK_UN) != -1);
    close(fdlock);
    unlink(LOCK_FILE);
}


int main(void) {
    check_lock();

    do_stuff();

    clean_up();

    return 0;
}


