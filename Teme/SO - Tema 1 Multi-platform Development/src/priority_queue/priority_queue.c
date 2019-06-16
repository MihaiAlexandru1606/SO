/**
 * @file : priority_queue.c
 *
 * @author : mihai
 */
#include <stdio.h>

#include "priority_queue.h"

int create_priority_queue(Priority_Queue **pPriority_queue, Type_Funct_Cmp cmp)
{
	int rez = ALOC_SUCCESS;

	if (pPriority_queue == NULL)
		exit(EXIT_FAILURE);

	*pPriority_queue = malloc(sizeof(Priority_Queue));
	if (*pPriority_queue == NULL) {
		rez = ENOMEM;
		goto exit;
	}

	(*pPriority_queue)->head = NULL;
	(*pPriority_queue)->cmp = cmp;

exit:
	return rez;
}

int add_priority_queue(Priority_Queue *priority_queue, const char *word,
		       int32_t priority)
{
	int rez = ADD_SUCCESS;
	size_t len_word;
	char *word_copy;
	size_t i;
	Cell *new_node;
	Cell **iterator;

	if (priority_queue == NULL) {
		rez = NULL_PQ;
		goto exit;
	}

	if (word == NULL) {
		rez = NULL_WORD;
		goto exit;
	}

	len_word = strlen(word);
	word_copy = malloc((len_word + 1) * sizeof(char));
	if (word_copy == NULL) {
		rez = ENOMEM;
		goto exit;
	}
	for (i = 0; i < len_word + 1; ++i)
		word_copy[i] = word[i];

	iterator = &(*priority_queue).head;
	while (*iterator != NULL) {
		if (compare((*iterator)->priority, priority) < 0)
			break;

		iterator = &(*iterator)->next;
	}

	new_node = malloc(sizeof(Cell));
	if (new_node == NULL) {
		free(word_copy);
		rez = ENOMEM;
		goto exit;
	}

	new_node->word = word_copy;
	new_node->priority = priority;
	new_node->next = *iterator;
	*iterator = new_node;

exit:
	return rez;
}

char *top_priority_queue(Priority_Queue *priority_queue)
{
	if (priority_queue == NULL)
		return NULL;
	if (priority_queue->head == NULL)
		return NULL;

	return priority_queue->head->word;
}

void pop_priority_queue(Priority_Queue *priority_queue)
{
	Cell *aux;

	if (priority_queue == NULL)
		return;
	if (priority_queue->head == NULL)
		return;

	aux = priority_queue->head;
	priority_queue->head = aux->next;
	free(aux->word);
	free(aux);
}

void destroy_priority_queue(Priority_Queue **pPriority_Queue)
{
	Cell *aux;

	while ((*pPriority_Queue)->head != NULL) {
		aux = (*pPriority_Queue)->head;
		(*pPriority_Queue)->head = aux->next;

		free(aux->word);
		free(aux);
	}

	free(*pPriority_Queue);
	*pPriority_Queue = NULL;
}
