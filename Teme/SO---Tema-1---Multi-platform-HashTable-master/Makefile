CC = cl
CFLAGS = /W4 /nologo /D_CRT_SECURE_NO_DEPRECATE
INCLUDE = /I .\src\utils /I .\src\linkedlist /I .\src\hashtable
EXE = tema1.exe
SIZE = 100

build: $(EXE)

tema1.exe: main.obj linkedlist.obj hashtable.obj parser.obj hash.lib
	$(CC) $(CFLAGS) $** /Fe$@

main.obj: .\src\main.c
	$(CC) $(CFLAGS) .\src\main.c /Fo$@ /c  

linkedlist.obj: .\src\linkedlist\linkedlist.c
	$(CC) $(CFLAGS) .\src\linkedlist\linkedlist.c /Fo$@ /c 

hashtable.obj: .\src\hashtable\hashtable.c
	$(CC) $(CFLAGS) .\src\hashtable\hashtable.c /Fo$@ /c 

parser.obj: .\src\parser\parser.c
	$(CC) $(CFLAGS) .\src\parser\parser.c /Fo$@ /c

run: tema1.exe
	.\tema1 $(SIZE)

.PHONY: clean

clean:
	del *.obj tema1.exe
