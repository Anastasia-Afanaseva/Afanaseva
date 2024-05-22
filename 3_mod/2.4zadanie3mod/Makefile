prog: 2.4.o
	gcc 2.4.o -o prog

prog_1: tmp.o
	gcc tmp.o -o prog_1

2.4.o: 2.4.c
	gcc -c 2.4.c

tmp.o: tmp.c
	gcc -c tmp.c

clean:
	rm -rf *.o prog

