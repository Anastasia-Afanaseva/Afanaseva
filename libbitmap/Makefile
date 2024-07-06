CC = gcc

CFLAGS = -g -I include -DSYSLOG
LIB_OBJ_OPT = -fPIC -Wall
LIB_OPT = -shared -Wall
PLUGIN_DIR = plugin
BUILD_DIR = build
SRC_DIR = src

OBJ = bitmap.o plugin.o log.o stress_test.o unit_test.o

%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIB_OBJ_OPT)

TARGET = libbitmap.so

libbitmap.so: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIB_OPT)

all: checkdir $(TARGET)
	mkdir -p $(BUILD_DIR)
	mv *.so $(BUILD_DIR)
	rm -rf $(OBJ)
	make -C $(PLUGIN_DIR) all

checkdir:
	if [ -d $(BUILD_DIR) ]; then       \
		rm -rf $(BUILD_DIR);           \
	fi

.PHONY: clean

clean:
	rm -rf *.o $(TARGET) $(BUILD_DIR)
	make -C $(PLUGIN_DIR) clean

.PHONY: all clean
