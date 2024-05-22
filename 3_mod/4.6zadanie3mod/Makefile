all: prog

prog: 4.6.o funk.o
	gcc 4.6.o funk.o -lrt -o prog

4.6.o: 4.6.c
	gcc -c 4.6.c

funk.o: funk.c
	gcc -c funk.c

clean:
	rm -rf *.o prog