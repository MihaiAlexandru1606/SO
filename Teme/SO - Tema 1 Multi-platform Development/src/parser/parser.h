/**
 * @file : parser.h
 *
 * @author : mihai
 */

#ifndef TEMA_1_PARSER_H
#define TEMA_1_PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "priority_queue.h"

#define DELIM			" \n\r\t\b"
#define BUFFER_SIZE		20000

#define IGNORE_COMMAND		0
#define SUCCESS_COMMAND		0

#define INSERT_COMMAND		"insert"
#define TOP_COMMAND		"top"
#define POP_COMMAND		"pop"
#define STRING_EQUAL		0

int read_file(Priority_Queue *priority_queue, FILE *in_stream);

#endif
