#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void)
{
	int ii = 0;
	int id;

	id = fork();

	if (id > 0) {
		printf("\tI creat you 1 %d -> %d\n ", getpid(), id);
		ii++;
	}
	wait(NULL);

	id = fork();
	if (id == 0) {
		ii++;
	} else printf("\t\tI creat you 2 %d -> %d\n ", getpid(), id);

	wait(NULL);

	id = fork();
	if (id < 0) { ii++; }
	else if (id > 0)
		printf("\t\t\tI creat you 3 %d -> %d\n ", getpid(), id);
	wait(NULL);
	printf("Result %d %p, id %d\n", ii, &ii, getpid());

	return 0;
}


	 
