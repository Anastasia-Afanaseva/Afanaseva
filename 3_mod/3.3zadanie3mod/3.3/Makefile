all: client

client: client.o
	gcc client.o -lrt -o client

client.o: client.c
	gcc -c client.c

clean:
	rm -rf *.o client