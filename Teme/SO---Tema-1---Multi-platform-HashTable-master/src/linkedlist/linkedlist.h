/**
 * @author : Niculescu Mihai Alexandru
 */
#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#pragma pack(1)
typedef struct node {
    char *info;
    struct node *next;
} Node, *LinkedList;
#pragma pack()

#define ADD_ERROR       -10
#define ADD_SUCCESS     0

#define SIZE_VID_LIST   0

int add_word(LinkedList *pList, char *info);

BOOL find_word(LinkedList list, char *word);

void print_list(LinkedList list, FILE *out);

void delete_word(LinkedList *pList, char *word);

void delete_list(LinkedList *pList);

#endif
