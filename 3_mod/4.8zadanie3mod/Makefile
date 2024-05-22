all: prog

prog: 4.8.o funk.o
	gcc 4.8.o funk.o -o prog

4.8.o: 4.8.c
	gcc -c 4.8.c

funk.o: funk.c
	gcc -c funk.c

clean:
	rm -rf *.o prog