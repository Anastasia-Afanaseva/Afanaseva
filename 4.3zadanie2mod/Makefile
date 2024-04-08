all: prog

prog: btree.o cont.o main.o person.o society.o work.o
	gcc btree.o cont.o main.o person.o society.o work.o -o prog

main.o: main.c
	gcc -c main.c

btree.o: btree.c
	gcc -c btree.c

cont.o: cont.c
	gcc -c cont.c

person.o: person.c
	gcc -c person.c

society.o: society.c
	gcc -c society.c

work.o: work.c
	gcc -c work.c

clean:
	rm -rf *.o prog