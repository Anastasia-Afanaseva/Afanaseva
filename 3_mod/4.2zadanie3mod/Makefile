all: prog

prog: 4.2.o funk.o
	gcc 4.2.o funk.o -o prog

4.2.o: 4.2.c
	gcc -c 4.2.c

funk.o: funk.c
	gcc -c funk.c

clean:
	rm -rf *.o prog