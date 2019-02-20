CC := gcc
CFLAGS = -std=c99 -O0
all: asm

asm: asm.c ../lib/map.c ../lib/strTable.c ../lib/util.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o *.exe