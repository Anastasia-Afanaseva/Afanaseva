all: prog

prog: 4.3.o funk.o
	gcc 4.3.o funk.o -o prog

4.3.o: 4.3.c
	gcc -c 4.3.c

funk.o: funk.c
	gcc -c funk.c

clean:
	rm -rf *.o prog