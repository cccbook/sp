CC := gcc
CFLAGS = -std=c99 -O0
TARGET = run.o

all: $(TARGET)

$(TARGET): sum.c main.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o