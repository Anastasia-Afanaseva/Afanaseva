all: calc_prog

calc_prog: main.o calc.o
	gcc main.o calc.o -lm -o calc_prog

main.o: main.c
	gcc -c main.c

calc.o: calc.c
	gcc -c calc.c -o calc.o

clean:
	rm -rf *.o calc_prog