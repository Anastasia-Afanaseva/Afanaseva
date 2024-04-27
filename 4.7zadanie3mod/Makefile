all: prog

prog: 4.7.o funk.o
	gcc 4.7.o funk.o -o prog

4.7.o: 4.7.c
	gcc -c 4.7.c

funk.o: funk.c
	gcc -c funk.c

clean:
	rm -rf *.o prog