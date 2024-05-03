all: server

server: server.o func_serv.o
	gcc server.o func_serv.o -o server

server.o: server.c
	gcc -c server.c

func_serv.o: func_serv.c
	gcc -c func_serv.c

clean:
	rm -rf *.o server