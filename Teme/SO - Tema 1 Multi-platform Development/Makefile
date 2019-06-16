build: main.obj parser.obj priority_queue.obj
	cl /W3 /MD main.obj /D_CRT_SECURE_NO_DEPRECATE parser.obj priority_queue.obj compare.lib /Fetema1.exe 

main.obj: src\main.c src\parser\parser.h
	cl /c /W3 /MD src\main.c /D_CRT_SECURE_NO_DEPRECATE /Fomain.obj /Isrc\parser /Isrc\priority_queue

parser.obj: src\parser\parser.c src\parser\parser.h src\priority_queue\priority_queue.h
	cl /c /W3 /MD src\parser\parser.c /D_CRT_SECURE_NO_DEPRECATE /Foparser.obj /Isrc\parser /Isrc\priority_queue

priority_queue.obj: src\priority_queue\priority_queue.c src\priority_queue\priority_queue.h src\priority_queue\compare.h
	cl /c /W3 /MD src\priority_queue\priority_queue.c /D_CRT_SECURE_NO_DEPRECATE /Fpriority_queue.obj /Isrc\parser /Isrc\priority_queue

.PHONY: clean
clean:
	del *.obj tema1.exe 
