all: prog_1

prog_1: 3.1.1.o
	gcc 3.1.1.o -o prog_1

3.1.1.o: 3.1.1.c
	gcc -c 3.1.1.c

clean:
	rm -rf *.o prog_1