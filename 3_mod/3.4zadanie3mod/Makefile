all: send

send: send.o
	gcc send.o -lrt -o send

send.o: send.c
	gcc -c send.c

clean:
	rm -rf *.o send