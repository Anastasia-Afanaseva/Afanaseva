all: task1

task1: main.o task1.o
	gcc main.o task1.o -lm -o task1

main.o: main.c
	gcc -c main.c

task1.o: task1.c
	gcc -c task1.c -o task1.o

clean:
	rm -rf *.o task1