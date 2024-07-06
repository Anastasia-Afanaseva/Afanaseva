CC = gcc

CFLAGS = -g -I ../include -DSYSLOG
LIB_OBJ_OPT = -fPIC -Wall
LIB_OPT = -shared -Wall
BUILD_DIR = build

libpluginNAND.so: plugin_NAND.o
	$(CC) $< $(LIB_OPT) -o $@

libpluginNOR.so: plugin_NOR.o
	$(CC) $< $(LIB_OPT) -o $@

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(LIB_OBJ_OPT)

all: checkdir libpluginNOR.so libpluginNAND.so
	rm -rf *.o
	mkdir -p $(BUILD_DIR)
	mv *.so $(BUILD_DIR)

checkdir:
	if [ -d $(BUILD_DIR) ]; then       \
		rm -rf $(BUILD_DIR);           \
	fi

clean:
	rm -rf build
	rm -rf *.o
