all: prog

prog: 3.2.o
	gcc 3.2.o -o prog

3.2.o: 3.2.c
	gcc -c 3.2.c

clean:
	rm -rf *.o prog
