/**
 * @author : Niculescu Mihai Alexandru
 */
#include "paser.h"


/**
 * functia care verifica daca un string reprezinta un numar pozitiv
 * @param word cuvantul de verificat
 * @return TRUE daca este
 *         FALSE daca nu este
 */
BOOL isNumber(const char *word) {
    size_t len = strlen(word);
    size_t i;

    for (i = 0; i < len; i++) {
        if (word[i] >= '0' && word[i] <= '9')
            continue;

        return FALSE;
    }

    return TRUE;
}

/**
 * functia verifica daca parametri operatiei add lipsesc, daca exista
 * se creaza o copie a cuvantului ce este adaugata in tabela
 * @param hashTable hash unde se adauga cuvantul
 * @return MISSING_PARAMETER -> daca lipseste parametrul pentru add
 *         ALLOC_MEM_ERROR -> daca nu s-a putut aloca memoria
 *         SUCCESS_COMMAND -> daca s-a reusit adaugarea in hash
 */
static int add_command(HashTable *hashTable) {
    char *token = strtok(NULL, DELIM);
    char *word;
    int rez;

    if (token == NULL) {
        fprintf(stderr, "%s %s\n", MISSING_PARAMETER_MSG, ADD_USAGE);
        return MISSING_PARAMETER;
    }

    word = my_strdup(token);
    if (word == NULL) {
        fprintf(stderr, "%s\n", ADD_ERROR_MESSAGE);
        return ALLOC_MEM_ERROR;
    }

    rez = add(hashTable, word);
    if (rez != ADD_SUCCESS) {
        fprintf(stderr, "%s\n", ADD_ERROR_MESSAGE);
        return ALLOC_MEM_ERROR;
    }

    return SUCCESS_COMMAND;
}

/**
 * functia care elimina cuvantul din hash,
 * se verifica daca parametrul pentru remove lipseste
 * @param hashTable hash-ul curent
 * @return tot timpul SUCCESS_COMMAND
 */
static int delete_command(HashTable *hashTable) {
    char *token = strtok(NULL, DELIM);

    if (token == NULL) {
        fprintf(stderr, "%s %s\n", MISSING_PARAMETER_MSG, REMOVE_USAGE);
        return MISSING_PARAMETER;
    }

    delete(hashTable, token);

    return SUCCESS_COMMAND;
}

/**
 * functia care cauta cuvantul in hash
 * se verifica lipseste parametru, cuvantul de cautat, daca nu, se verifica daca
 * mai exista si alti parametri, fisierele de iesire, si se cauta in hash. Daca
 * este gasit este printat FIND_WORD in fisierele de iesire sau in caz contrar
 * NOT_FIND_WORD
 * @param hashTable hash cel mai smecher si cool
 * @return MISSING_PARAMETER -> daca lipseste parametrul obligatoriul
 *        SUCCESS_COMMAND -> daca nu lipseste parametrul, cuvantul
 */
static int find_command(HashTable *hashTable) {
    FILE *outstream = stdout;
    BOOL find_word;
    char *token = strtok(NULL, DELIM);

    if (token == NULL) {
        fprintf(stderr, "%s %s\n", MISSING_PARAMETER_MSG, FIND_USAGE);
        return MISSING_PARAMETER;
    }

    find_word = find(hashTable, token);
    /** verificarea daca exista specifiact fisire de iesirere */
    token = strtok(NULL, DELIM);
    do {
        if (token != NULL)
            outstream = fopen(token, "a");

        if (outstream == NULL) {
            /** daca nu s-a put deschide fisierul in mod append */
            continue;
        }

        if (find_word) {
            fprintf(outstream, "%s\n", FIND_WORD);
        } else {
            fprintf(outstream, "%s\n", NOT_FIND_WORD);
        }
        if (outstream != stdout) {
            fclose(outstream);
        }
        token = strtok(NULL, DELIM);
    } while (token != NULL);

    return SUCCESS_COMMAND;
}

/**
 * functia care printeaza bucket-ul indicat
 * se verifica daca parametrul este corect sau exista
 * se verifica daca se specifica fisierele de iesire, daca nu se printeaza la
 * stdout
 * @param hashTable tabela de dispersie
 * @return MISSING_PARAMETER -> daca lispseste index-ul
 *         INVALID_PARAMETER -> daca este incorect
 *         SUCCESS_COMMAND -> operatiune a avut loc cu succes
 *
 */
static int print_bucket_command(HashTable *hashTable) {
    FILE *outstream = stdout;
    size_t index;
    char *token = strtok(NULL, DELIM);


    if (token == NULL) {
        fprintf(stderr, "%s %s\n", MISSING_PARAMETER_MSG, PRINT_BUCKET_USAGE);
        return MISSING_PARAMETER;
    }

    if (isNumber(token) == FALSE) {
        /** nu este un numar intreg pozitiv */
        fprintf(stderr, "%s\n", INVALID_PARAMET_MESSAGE);
        fprintf(stderr, "%s\n", PRINT_BUCKET_USAGE);
        return INVALID_PARAMETER;
    }
    index = (size_t) atoi(token);
    if (index >= hashTable->size) {
        /** daca depaseste dimensiune tabelei in acel moment */
        fprintf(stderr, "%s\n", INVALID_PARAMET_MESSAGE);
        fprintf(stderr, "%s\n", PRINT_BUCKET_USAGE);
        return INVALID_PARAMETER;
    }

    /** verificarea daca exista specifiact fisire de iesirere */
    token = strtok(NULL, DELIM);
    do {
        if (token != NULL) {
            outstream = fopen(token, "a");
        }

        if (outstream == NULL) {
            /** daca nu s-a put deschide fisierul in mod append */
            continue;
        }

        print_bucket(hashTable, index, outstream);
        if (outstream != stdout) {
            fclose(outstream);
        }
        token = strtok(NULL, DELIM);
    } while (token != NULL);

    return SUCCESS_COMMAND;
}

/**
 * functia care printeaza tabela de dispersie
 * se verifica daca se specifica fisierele de iesire, daca nu se printeaza la
 * stdout
 * @param hashTable tabela de dispersie
 * @return tot timpul SUCCESS_COMMAND
 */
static int print_command(HashTable *hashTable) {
    FILE *outstream = stdout;
    char *token;

    /** verificarea daca exista specifiact fisire de iesirere */
    token = strtok(NULL, DELIM);
    do {
        if (token != NULL) {
            outstream = fopen(token, "a");
        }

        if (outstream == NULL) {
            /** daca nu s-a put deschide fisierul in mod append */
            continue;
        }

        print(hashTable, outstream);
        if (outstream != stdout) {
            fclose(outstream);
        }
        token = strtok(NULL, DELIM);
    } while (token != NULL);

    return SUCCESS_COMMAND;
}

/**
 * functia care realizeaza redimensionarea hash-ul
 * se verifica daca parametrul exista si daca el este corect
 * se creaza o noua tabela si este eliberata memeoria pentru vechia tabela
 * @param pHashTable adresa tabela de disperie
 * @return MISSING_PARAMETER -> daca lispseste parametrul
 *         INVALID_PARAMETER -> daca parametrul este incorect
 *         RESIZE_ERROR -> daca nu s-a putut creea noul hash
 *         SUCCESS_COMMAND -> daca se reuseste redimensionarea
 */
static int resize_command(HashTable **pHashTable) {
    char *token = strtok(NULL, DELIM);

    if (token == NULL) {
        fprintf(stderr, "%s %s\n", MISSING_PARAMETER_MSG, RESIZE_USAGE);
        return MISSING_PARAMETER;
    }

    if (strcmp(token, RESIZE_DOUBLE) == STRING_EQUAL) {
        *pHashTable = resize_double(pHashTable);
        if (*pHashTable == NULL) {
            fprintf(stderr, "%s\n", RESIZE_ERROR_MSG);
            return RESIZE_ERROR;
        }

        return SUCCESS_COMMAND;
    }

    if (strcmp(token, RESIZE_HALVE) == STRING_EQUAL) {
        *pHashTable = resize_halve(pHashTable);
        if (*pHashTable == NULL) {
            fprintf(stderr, "%s\n", RESIZE_ERROR_MSG);
            return RESIZE_ERROR;
        }

        return SUCCESS_COMMAND;
    }

    fprintf(stderr, "%s\n", INVALID_PARAMET_MESSAGE);
    fprintf(stderr, "%s\n", RESIZE_USAGE);
    return INVALID_PARAMETER;
}

/**
 * functia care incepe pasare inputului si decite ce comanda este
 * @param pHashTable adreresa tabelei de dispersie
 * @param line linia citira de la tastaura
 * @return SUCCESS_COMMAND in cazul in care s-a putut executa comanda sau daca
 *         un cod de erore
 */
static int parser_command(HashTable **pHashTable, char *line) {
    char *token = strtok(line, DELIM);

    if (strcmp(token, ADD_COMMAND) == STRING_EQUAL) {
        return add_command(*pHashTable);
    }

    if (strcmp(token, REMOVE_COMMAND) == STRING_EQUAL) {
        return delete_command(*pHashTable);
    }

    if (strcmp(token, FIND_COMMAND) == STRING_EQUAL) {
        return find_command(*pHashTable);
    }

    if (strcmp(token, CLEAR_COMMAND) == STRING_EQUAL) {
        clear_hash(*pHashTable);
        return SUCCESS_COMMAND;
    }

    if (strcmp(token, PRINT_BUCKET_COMMAND) == STRING_EQUAL) {
        return print_bucket_command(*pHashTable);
    }

    if (strcmp(token, PRINT_COMMAND) == STRING_EQUAL) {
        return print_command(*pHashTable);
    }

    if (strcmp(token, RESIZE_COMMAND) == STRING_EQUAL) {
        return resize_command(pHashTable);
    }

    /** daca este o comanda necunoscuta se printeza mesajul corespunzator */
    fprintf(stderr, "%s\n", UNKNOW_MESSAGE);
    return UNKNOW_COMMAND;
}

/**
 * functia care citeste din fisier si care pasease fiecare linie functuie
 *   paser_command
 * sunt evitate linile vide
 * @param pHashTable adresa tabela de dispersie
 * @param instream fisireul de intrare
 * @return SUCCESS_COMMAND in caz ca totul a funtionat normal sau altfel un cod
 *          de eroare
 */
int read_from_file(HashTable **pHashTable, FILE *instream) {
    char buffer[BUFFER_SIZE] = {0};
    int rez;

    while (fgets(buffer, BUFFER_SIZE, instream)) {
        /** evitarea liniilor vide */
        if (buffer[0] == '\n')
            continue;

        rez = parser_command(pHashTable, buffer);

        if (rez == SUCCESS_COMMAND) {
            memset(buffer, 0, BUFFER_SIZE);
            continue;
        }

        return rez;
    }

    return SUCCESS_COMMAND;
}