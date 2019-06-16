/**
 * SO, 2010 - Lab #2, Simple I/O
 * Task #4, Linux
 *
 * Standard output/error redirection
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
	
	
int main(void)
{
	int old_fd_out, old_fd_err;
	int file = open("File.txt", O_RDWR | O_CREAT, 0644);
	dup2(file, STDOUT_FILENO);

	old_fd_out = dup(STDOUT_FILENO);
	old_fd_err = dup(STDERR_FILENO);

	close(STDERR_FILENO);
	close(STDOUT_FILENO);

	dup(old_fd_err);
	dup(old_fd_out);

	fputs("alfa\n", stderr);
	fputs("beta\n", stdout);

	return 0;
}

	
