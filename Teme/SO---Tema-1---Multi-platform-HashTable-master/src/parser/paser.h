/**
 * @author : Niculescu Mihai Alexandru
 */
#ifndef _PASER_H
#define _PASER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "hashtable.h"

/** operatiuniele  pentru hash*/
#define ADD_COMMAND             "add"
#define REMOVE_COMMAND          "remove"
#define FIND_COMMAND            "find"
#define CLEAR_COMMAND           "clear"
#define PRINT_BUCKET_COMMAND    "print_bucket"
#define PRINT_COMMAND           "print"
#define RESIZE_COMMAND          "resize"
#define RESIZE_DOUBLE           "double"
#define RESIZE_HALVE            "halve"

#define DELIM                    " \n\r\t\b"

/** coduri de return pentru operati **/
#define SUCCESS_COMMAND         0
#define MISSING_PARAMETER       -1
#define ALLOC_MEM_ERROR         -2
#define INVALID_PARAMETER       -3
#define RESIZE_ERROR            -4
#define UNKNOW_COMMAND          -5

/** mesajele in caz de erore **/
#define UNKNOW_MESSAGE          "The unknown command!"
#define ALLOC_HASH_MESSAGE      "I can not create hash!"
#define INVALID_PARAMET_MESSAGE "Incorrect parameters!"
#define ADD_ERROR_MESSAGE       "I can not add the word!"
#define MISSING_PARAMETER_MSG   "Missing parameter: "
#define ADD_USAGE               "add <cuvânt>"
#define REMOVE_USAGE            "remove <cuvânt>"
#define FIND_USAGE              "find <cuvânt> [<fișier_ieșire>]"
#define PRINT_BUCKET_USAGE      "print_bucket <index_bucket> [<fișier_ieșire>]"
#define RESIZE_USAGE            "resize double | halve"
#define RESIZE_ERROR_MSG        "I can not create new hash!"

#define FIND_WORD               "True"
#define NOT_FIND_WORD           "False"

BOOL isNumber(const char *word);

int read_from_file(HashTable **pHashTable, FILE *instream);

#endif
