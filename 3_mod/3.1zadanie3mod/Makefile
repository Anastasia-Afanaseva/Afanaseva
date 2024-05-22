all: prog

prog: 3.1.o
	gcc 3.1.o -o prog

3.1.o: 3.1.c
	gcc -c 3.1.c

clean:
	rm -rf *.o prog