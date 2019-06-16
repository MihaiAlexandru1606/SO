/**
 * @file : priority_queue.h
 *
 * @author : mihai
 */

#ifndef TEMA_1_PRIORITY_QUEUE_H
#define TEMA_1_PRIORITY_QUEUE_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "compare.h"

#define ALOC_SUCCESS	0

#define ENOMEM		12
#define ADD_SUCCESS	0
#define NULL_PQ		-1
#define NULL_WORD	-2

#pragma pack(1)

typedef int (*Type_Funct_Cmp)(int priorty1, int priorty2);

typedef struct cell {
	char *word;
	int32_t priority;
	struct cell *next;
} Cell;

typedef struct {
	Cell *head;
	Type_Funct_Cmp cmp;
} Priority_Queue;

#pragma pack()

/**
 * functia care creeaza/initializeaza coada cu prioiritate
 * @param pPriority_queue adresa unui pointer de tipul Priority_Queue
 * @param cmp functia de comparare pentru prioritati
 * @return ALOC_SUCCESS in cazul in care s-a realizat cu succes alocarea de
 *	   memorie; ENOMEM in caz contrar
 */

int
create_priority_queue(Priority_Queue * *pPriority_queue, Type_Funct_Cmp cmp);

/**
 * functia insereaza in coada c perechia (cuvant, prioritate), inserarea se face
 * ordonat (se cauat prima perechie care nu are prioritate mai mica, apoi se
 * insereaza inaintea ei)
 * @param priority_queue adresa cozi cu prioritate
 * @param word cuvantul inserat
 * @param priority prioritatea cuvantului
 * @return NULL_PQ     -> nu este alocata memoria pentru coada
 *	   NULL_WORD   -> cuvanul este null
 *	   ENOMEM      -> nu s-a putat aloca memoria
 *	   ADD_SUCCESS -> inserarea reusita
 */

int add_priority_queue(Priority_Queue *priority_queue, const char *word,
			 int32_t priority);

/**
 * functia returneaza cuvantul care are prioritate cea mai mare, daca coada nu
 * este goala
 * @param priority_queue coada cuvprioritate
 * @return NULL -> coada goala;
 *	   adresa cuvantului cu cea mai mare prioritate
 */

char *top_priority_queue(Priority_Queue *priority_queue);

/**
 * functia elimina cuvantul care are prioritate cea mai mare, daca coada nu este
 * goala
 * @param pPriority_Queue coada cu prioritate
 */

void pop_priority_queue(Priority_Queue *priority_queue);

/**
 * functia elimina toate elementele din coada si dealoca mememoria pentru
 * strcutura pentru coada
 * @param pPriority_Queue adresa unui pointer de tipul Priority_Queue
 */

void destroy_priority_queue(Priority_Queue **pPriority_Queue);

#endif
