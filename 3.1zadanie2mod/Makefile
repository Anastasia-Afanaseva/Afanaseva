all: prog

prog: main.o func_1.o func_2.o func_3.o
	gcc main.o func_1.o func_2.o func_3.o -o prog

main.o: main.c
	gcc -c main.c

func_1.o: func_1.c
	gcc -c func_1.c

func_2.o: func_2.c
	gcc -c func_2.c

func_3.o: func_3.c
	gcc -c func_3.c

clean:
	rm -rf *.o prog