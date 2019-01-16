CC := gcc
CFLAGS = -std=c99 -O0
all: asm

asm: asm.c c6.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o *.exe