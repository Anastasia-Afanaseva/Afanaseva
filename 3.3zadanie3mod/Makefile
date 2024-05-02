all: server

server: server.o
	gcc server.o -lrt -o server

server.o: server.c
	gcc -c server.c

clean:
	rm -rf *.o server