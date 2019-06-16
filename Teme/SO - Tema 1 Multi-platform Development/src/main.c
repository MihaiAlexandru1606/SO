/**
 * @file : main.c
 *
 * @author : mihai
 */
#include <stdio.h>
#include "parser.h"
#include <assert.h>

int main(int argc, char **argv)
{
	Priority_Queue *priority_queue = NULL;
	int i;
	FILE *in_stream = stdin;
	int rez;

	rez = create_priority_queue(&priority_queue, compare);
	if (rez == ENOMEM)
		return rez;

	if (argc == 1) {
		rez = read_file(priority_queue, in_stream);

		destroy_priority_queue(&priority_queue);
		return rez;
	}

	for (i = 1; i < argc; i++) {
		in_stream = fopen(argv[i], "r");
		if (in_stream == NULL)
			continue;

		rez = read_file(priority_queue, in_stream);
		assert(fclose(in_stream) == 0);
		if (rez == ENOMEM) {
			destroy_priority_queue(&priority_queue);
			return rez;
		}
	}

	destroy_priority_queue(&priority_queue);
	return EXIT_SUCCESS;
}
