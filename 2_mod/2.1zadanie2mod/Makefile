all: program

program: main.o task1.o cont.o person.o society.o work.o
	gcc main.o task1.o cont.o person.o society.o work.o -o program

main.o: main.c
	gcc -c main.c

cont.o: cont.c
	gcc -c cont.c

person.o: person.c
	gcc -c person.c

society.o: society.c
	gcc -c society.c

work.o: work.c
	gcc -c work.c

task1.o: task1.c
	gcc -c task1.c -o task1.o

clean:
	rm -rf *.o program