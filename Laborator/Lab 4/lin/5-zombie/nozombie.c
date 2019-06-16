/**
  * SO, 2016
  * Lab #4
  *
  * Task #5, lin
  *
  * Avoid creating zombies using signals
  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#include "utils.h"

#define TIMEOUT		20


/*
 * configure signal handler
 */
static void set_signals(void)
{
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));

	/* TODO - ignore SIGCHLD */

}

int main(void)
{
	pid_t pid;
	int rc;

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	rc = sigaction(SIGCHLD, &sa, NULL);
	DIE(rc == -1, "sigaction");

	/* TODO - create child process without waiting */
	pid = fork();
	if (pid == 0){
		exit(EXIT_SUCCESS);
	}

	/* TODO - sleep */
	sleep(TIMEOUT);

	return 0;
}
