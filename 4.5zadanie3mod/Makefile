all: prog

prog: 4.5.o func.o
	gcc 4.5.o func.o -lrt -o prog

4.5.o: 4.5.c
	gcc -c 4.5.c

func.o: func.c
	gcc -c func.c

clean:
	rm -rf *.o prog