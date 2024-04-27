all: prog

prog: 4.9.o funk.o
	gcc 4.9.o funk.o -lrt -o prog

4.9.o: 4.9.c
	gcc -c 4.9.c

funk.o: funk.c
	gcc -c funk.c

clean:
	rm -rf *.o prog