CC := gcc
CFLAGS = -O0 -std=gnu99 -Wall -Werror
TARGET = c0c
all: $(TARGET)

$(TARGET): c0c.c compiler.c lexer.c map.c scan.c strTable.c util.c vm.c x86.c
	$(CC) $(CFLAGS) $^ -o $(TARGET)

clean:
	rm *.o *.exe