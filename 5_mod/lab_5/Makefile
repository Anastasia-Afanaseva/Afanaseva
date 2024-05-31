obj-m += netlink.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc user.o -o user

user: user.c
	gcc -c user.c

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f user user.o