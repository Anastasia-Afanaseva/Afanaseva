all: tmp

tmp: tmp.o
	gcc tmp.o -o tmp

tmp.o: tmp.c
	gcc -c tmp.c

clean:
	rm -rf *.o tmp