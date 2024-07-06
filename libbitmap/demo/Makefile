CC = gcc

INCLUDE_PATH = -g -I ../include -DSYSLOG
LIBS_PATH = ../build
LIBS = -lbitmap -ldl
BIN_FLAGS = -Wl,-rpath,../$(LIBS_PATH) -Wall
OBJ_FLAGS = -Wall
BUILD_DIR = build

OBJ = main.o

TARGET = demo

%.o: %.c
	$(CC) -c -o $@ $< $(OBJ_FLAGS) $(INCLUDE_PATH)

$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) -L $(LIBS_PATH) $(BIN_FLAGS) $(LIBS)
	rm -rf *.o

all: build_lib checkdir $(TARGET)
	mkdir -p $(BUILD_DIR)
	mv $(TARGET) $(BUILD_DIR)
	rm -rf $(OBJ)

build_lib:
	make -C .. all

checkdir:
	if [ -d $(BUILD_DIR) ]; then       \
		rm -rf $(BUILD_DIR);           \
	fi

clean:
	rm -rf *.o $(TARGET) $(BUILD_DIR)
	make -C .. clean
