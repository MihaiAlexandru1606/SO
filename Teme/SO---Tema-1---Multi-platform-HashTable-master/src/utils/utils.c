/**
 * @author : Niculescu Mihai Alexandru
 */
#include "utils.h"

/**
 * implementarea pentru strdup, deoarece functia nu este in standard-ul C
 */
char *my_strdup(const char *string) {
    char *duplicat;
    int i, len = 0;

    while (string[len] != '\0') {
        ++len;
    }

    duplicat = (char *) malloc((len + 1) * sizeof(char));
    if (duplicat != NULL) {
        for (i = 0; i < len; i++) {
            duplicat[i] = string[i];
        }

        duplicat[len] = '\0';
    }

    return duplicat;
}
