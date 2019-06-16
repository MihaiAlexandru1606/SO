/**
 * @author : Niculescu Mihai Alexandru
 */
#ifndef _UTILS_H
#define _UTILS_H

#include <stdlib.h>

/** tipul de date "bool", stdbool.h nu merge in Windows ... */
#define BOOL                int
#define TRUE                1
#define FALSE               0

#define BUFFER_SIZE         20000

#define ERROR_USAGE_MASSAGE "Usage : %s <size_hashtable> [<file>]\n"

#define STRING_EQUAL         0

#define EXIT_ERROR          -1

char *my_strdup(const char *string);

#endif
