CC = gcc
CFLAGS = -Wall -Werror -Wextra
SIZE=100 
INCLUDE = -I ./src/utils -I ./src/linkedlist -I ./src/hashtable

build: tema1

tema1: main.o linkedlist.o hashtable.o parser.o utils.o
	$(CC) $(CFLAGS) main.o linkedlist.o hashtable.o parser.o utils.o -o tema1 -lhash -L. $(INCLUDE)

main.o: src/main.c
	$(CC) $(CFLAGS) src/main.c -c $(INCLUDE)

linkedlist.o: src/linkedlist/linkedlist.c
	$(CC) $(CFLAGS) src/linkedlist/linkedlist.c -c $(INCLUDE)

hashtable.o: src/hashtable/hashtable.c
	$(CC) $(CFLAGS) src/hashtable/hashtable.c -c $(INCLUDE)

parser.o: src/parser/parser.c
	$(CC) $(CFLAGS) src/parser/parser.c -c $(INCLUDE)

utils.o: src/utils/utils.c
	$(CC) $(CFLAGS) src/utils/utils.c -c $(INCLUDE)

run: tema1
	./tema1 ${SIZE}

.PHONY: clean

clean:
	rm -fr *.o tema1
