all: program

program: main.o item.o libcont_item.a
	gcc main.o item.o -L. -lcont_item -o program

main.o: main.c
	gcc -c -Wall main.c -std=c99

libcont_item.a: cont.o person.o society.o work.o
	ar cr libcont_item.a cont.o person.o society.o work.o

cont.o: cont.c
	gcc -c -Wall cont.c -std=c99

person.o: person.c
	gcc -c -Wall person.c -std=c99

society.o: society.c
	gcc -c -Wall society.c -std=c99

work.o: work.c
	gcc -c -Wall work.c -std=c99
	
item.o: item.c
	gcc -c -Wall item.c -std=c99 

clean:
	rm -rf *.o *.a program
