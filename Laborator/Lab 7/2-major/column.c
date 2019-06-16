/**
 * SO, 2017 - Lab #07, Profiling
 * Task #2, Linux
 *
 * Row major
 */
#include <stdio.h>

#define SIZE 4096

char x[SIZE][SIZE];

int
main(void)
{
	int i, j;

	for (j = 0; j < SIZE; ++j) {
		for (i = 0; i < SIZE; ++i) {
			x[i][j] += 12 * i + j * i + i * i;
		}
	}
	
	int sum = 0;
	for (j = 0; j < SIZE; ++j) {
		for (i = 0; i < SIZE; ++i) {
			sum += x[i][j];
		}
	}
	printf("%d\n", sum);
	
	return 0;
}
