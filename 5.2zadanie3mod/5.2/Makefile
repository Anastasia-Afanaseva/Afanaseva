all: client_2

client_2: client_2.o
	gcc client_2.o -o client_2

client_2.o: client_2.c
	gcc -c client_2.c

clean:
	rm -rf *.o client_2