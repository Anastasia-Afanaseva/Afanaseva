all: rec

rec: recieve.o
	gcc recieve.o -lrt -o rec

recieve.o: recieve.c
	gcc -c recieve.c

clean:
	rm -rf *.o rec