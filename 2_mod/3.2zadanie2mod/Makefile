all: my_prog

my_prog: main.o funk.o
	gcc main.o funk.o -o my_prog

main.o: main.c
	gcc -c main.c

funk.o: funk.c
	gcc -c funk.c

clean:
	rm -rf *.o my_prog