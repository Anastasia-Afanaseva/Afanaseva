all: prog

prog: 3.5.o funk.o
	gcc 3.5.o funk.o -lrt -o prog

3.5.o: 3.5.c
	gcc -c 3.5.c

funk.o: funk.c
	gcc -c funk.c

clean:
	rm -rf *.o prog