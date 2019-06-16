CC = gcc
CFLAGS = -Wall -Werror -Wextra
INCLUDE = -I ./src/utils -I ./src/priority_queue -I ./src/parser

build: tema1

tema1: main.o priority_queue.o parser.o
	$(CC) $(CFLAGS) main.o priority_queue.o parser.o -o tema1 -lcompare -L. $(INCLUDE)

main.o: src/main.c src/parser/parser.h
	$(CC) $(CFLAGS) src/main.c -c $(INCLUDE)

priority_queue.o: src/priority_queue/priority_queue.c src/priority_queue/priority_queue.h src/priority_queue/compare.h
	$(CC) $(CFLAGS) src/priority_queue/priority_queue.c -c $(INCLUDE)

parser.o: src/parser/parser.c src/parser/parser.h src/priority_queue/priority_queue.h
	$(CC) $(CFLAGS) src/parser/parser.c -c $(INCLUDE)

.PHONY: clean
clean:
	rm -fr *.o tema1
