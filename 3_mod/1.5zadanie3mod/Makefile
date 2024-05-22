all: program

program: main.o item.o libcont.so
	gcc main.o item.o -L. -lcont -o program

main.o: main.c
	gcc -c -Wall main.c -std=c99

libcont.so: cont.o person.o society.o work.o
	gcc -shared -o libcont.so cont.o person.o society.o work.o

cont.o: cont.c
	gcc -c -fPIC -Wall cont.c -std=c99

person.o: person.c
	gcc -c -fPIC -Wall person.c -std=c99

society.o: society.c
	gcc -c -fPIC -Wall society.c -std=c99

work.o: work.c
	gcc -c -fPIC -Wall work.c -std=c99
	
item.o: item.c
	gcc -c -Wall item.c -std=c99 

clean:
	rm -rf *.o program

