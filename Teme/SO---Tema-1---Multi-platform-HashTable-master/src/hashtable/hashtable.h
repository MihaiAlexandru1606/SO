/**
 * @author : Niculescu Mihai Alexandru
 */
#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "linkedlist.h"
#include "hash.h"
#include "utils.h"

#pragma pack(1)

typedef struct {
    unsigned int size;
    LinkedList *buckets;
} HashTable;

#pragma pack()

HashTable *init_hash(unsigned int capacity);

int add(HashTable *hashTable, char *word);

BOOL find(HashTable *hashTable, char *word);

void delete(HashTable *hashTable, char *word);

void print_bucket(HashTable *hashTable, size_t indexBucket, FILE *out);

void print(HashTable *hashTable, FILE *out);

HashTable *resize_halve(HashTable **pHashTable);

HashTable *resize_double(HashTable **pHashTable);

void clear_hash(HashTable *hashTable);

void destroy_hash(HashTable **pHashTable);

#endif
