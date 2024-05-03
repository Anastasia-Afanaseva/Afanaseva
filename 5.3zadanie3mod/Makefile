all: client

client: client.o func_client.o
	gcc client.o func_client.o -o client

client.o: client.c
	gcc -c client.c

func_client.o: func_client.c
	gcc -c func_client.c

clean:
	rm -rf *.o client