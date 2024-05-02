all: client_1

client_1: client_1.o
	gcc client_1.o -o client_1

client_1.o: client_1.c
	gcc -c client_1.c

clean:
	rm -rf *.o client_1