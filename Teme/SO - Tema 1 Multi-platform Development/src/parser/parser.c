/**
 * @file : parser.c
 *
 * @author : mihai
 */
#include "parser.h"

/**
 * functia verifica daca parametri pentru insert sunt corecti, daca da atunci
 * apeleaza add_priority_queue, altfel "ignora comanda"
 * @param priority_queue coda unde se insereaza cuvantul si prioritatea
 * @return IGNORE_COMMAND -> daca paramentri nu sunt corecti, altfel
 *	    rezultaul intors de functie add_priority_queue
 */
static int insert_commnad(Priority_Queue *priority_queue)
{

	char *token;
	char *word;
	int32_t priority;
	size_t len_word;
	size_t i;

	/** verificam daca exista cuvanatul si respaecta forma [a-z]+*/
	word = strtok(NULL, DELIM);
	if (word == NULL)
		return IGNORE_COMMAND;

	len_word = strlen(word);
	for (i = 0; i < len_word; i++) {
		if (word[i] < 'a' || word[i] > 'z')
			return IGNORE_COMMAND;
	}

	/** daca al doilea argument exista si reprezinta un numar */
	token = strtok(NULL, DELIM);
	if (token == NULL)
		return IGNORE_COMMAND;
	priority = atoi(token);
	if (priority == 0 && (token[0] != '0' || strlen(token) > 1))
		return IGNORE_COMMAND;

	/** daca nu mai exista si alte argumente */
	token = strtok(NULL, DELIM);
	if (token != NULL)
		return IGNORE_COMMAND;

	return add_priority_queue(priority_queue, word, priority);
}

/**
 * functia verifica daca respecta formatul pentru comanda top, daca da apeleaza
 * top_priority_queue, daca coada cu prioritate este goala atunci printeza '\n'
 * @param priority_queue coda unde se aplica top
 * @return daca paramentri sunt corecti atunci returneaza SUCCESS_COMMAND,
 *	   altfel IGNORE_COMMAND
 */
static int top_command(Priority_Queue *priority_queue)
{
	char *token;
	char *word;

	token = strtok(NULL, DELIM);
	if (token != NULL)
		return IGNORE_COMMAND;

	word = top_priority_queue(priority_queue);

	if (word == NULL)
		printf("\n");
	else
		printf("%s\n", word);

	return SUCCESS_COMMAND;
}

/**
 * functia verifica daca respecta formatul pentru comanda pop, daca da :
 * apeleaza pop_priority_queue
 * @param priority_queue coada	asupra carei se aplica operatiunea
 * @return daca paramentri sunt corecti atunci returneaza SUCCESS_COMMAND,
 *	   altfel IGNORE_COMMAND
 */
static int pop_command(Priority_Queue *priority_queue)
{
	char *token;

	/** daca nu mai exista si alte argumente */
	token = strtok(NULL, DELIM);
	if (token != NULL)
		return IGNORE_COMMAND;

	pop_priority_queue(priority_queue);

	return SUCCESS_COMMAND;
}

/**
 * functia paseaza lini si identifica primul token, daca corespunde unei
 * operati descrise in enunt se apeleaza functia corespunzatore, altfel se
 * ignora
 * @param priority_queue coada asupra carei se aplica operatiunea
 * @param line linia citita
 * @return ce returneza fiecare functie corespunzatoare unie comenzi,
 *	   altfel IGNORE_COMMAND
 */
static int parser_command(Priority_Queue *priority_queue, char *line)
{
	char *token = strtok(line, DELIM);

	if (token == NULL)
		return IGNORE_COMMAND;

	if (strcmp(INSERT_COMMAND, token) == STRING_EQUAL)
		return insert_commnad(priority_queue);

	if (strcmp(TOP_COMMAND, token) == STRING_EQUAL)
		return top_command(priority_queue);

	if (strcmp(POP_COMMAND, token) == STRING_EQUAL)
		return pop_command(priority_queue);

	return IGNORE_COMMAND;
}

/**
 * fumctia citeste o line din fisier care apoi tokenizata
 * @param priority_queue coada asupra carei se aplica operatiunea
 * @param in_stream fisierul unde se citeste
 * @return daca nu s-a putut aloca memoria se returneaza ENOMEM,
 *	   altfel SUCCESS_COMMAND
 */
int read_file(Priority_Queue *priority_queue, FILE *in_stream)
{
	char buffer[BUFFER_SIZE] = {0,};
	int rez;

	while (fgets(buffer, BUFFER_SIZE, in_stream)) {

		rez = parser_command(priority_queue, buffer);

		if (rez != ENOMEM) {
			memset(buffer, 0, BUFFER_SIZE);
			continue;
		}

		return rez;
	}

	return SUCCESS_COMMAND;
}
