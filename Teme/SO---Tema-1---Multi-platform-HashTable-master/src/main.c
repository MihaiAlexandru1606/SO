/**
 * @author : Niculescu Mihai Alexandru
 */
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "hashtable.h"
#include "paser.h"

int main(int argc, char **argv) {
    unsigned int size_hash;
    int i;
    int rez;
    FILE *istream = stdin;
    HashTable *hashTable;

    if (argc < 2) {
        /** daca nu sunt parametri corecti */
        fprintf(stderr, ERROR_USAGE_MASSAGE, argv[0]);
        exit(EXIT_ERROR);
    }

    if (isNumber(argv[1]) == FALSE) {
        /** daca al doilea parametru nu este un numar pozitiv */
        fprintf(stderr, "%s\n", INVALID_PARAMET_MESSAGE);
        fprintf(stderr, ERROR_USAGE_MASSAGE, argv[0]);
        exit(EXIT_ERROR);
    }

    size_hash = (unsigned int) atoi(argv[1]);
    hashTable = init_hash(size_hash);
    if (hashTable == NULL) {
        /** nu s-a put aloca memoria pentru HashTable */
        fprintf(stderr, "%s\n", ALLOC_HASH_MESSAGE);
        exit(EXIT_ERROR);
    }

    if (argc == 2) {
        /** citirea de la stdin */
        read_from_file(&hashTable, istream);
    } else {
        for (i = 2; i < argc; ++i) {
            istream = fopen(argv[i], "r");
            /** se ingnora fisierele care nu s-au putut descidere in mod read */
            if (istream == NULL)
                continue;

            rez = read_from_file(&hashTable, istream);
            fclose(istream);

            if (rez != SUCCESS_COMMAND) {
                /** daca la executarea unei comenzi a aparut o eroare */
                if (hashTable)
                    destroy_hash(&hashTable);
                exit(EXIT_ERROR);
            }
        }
    }

    destroy_hash(&hashTable);
    return 0;
}
