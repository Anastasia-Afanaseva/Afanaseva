all: tmp

tmp: tmp.o
	gcc tmp.o -lrt -o tmp

tmp.o: tmp.c
	gcc -c tmp.c

clean:
	rm -rf *.o tmp