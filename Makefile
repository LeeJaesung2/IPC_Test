CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lpthread

BUILD = ./build
EXECUTABLE=$(BUILD)/main.exe
SRC=$(wildcard ./*.c)
OBJ=$(SRC:./%.c=$(BUILD)/%.o)
$(shell mkdir -p $(BUILD))

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJ)
	$(CC) $^ -o $(EXECUTABLE) $(LDFLAGS)

$(BUILD)/%.o: ./%.c
	$(CC) $(CFLAGS) $< -o $@ 


clear:
	rm -rf $(BUILD)/*.o $(BUILD)/*.exe

exe:
	$(EXECUTABLE)

