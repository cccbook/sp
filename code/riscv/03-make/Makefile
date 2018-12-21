CC := riscv64-unknown-elf-gcc
CFLAGS = -std=c99 -O0
TARGET = run.o
ASMS = sum.s main.s

all: $(TARGET)

run:
	spike pk $(TARGET)

asm: $(ASMS)
	$(CC) $(CFLAGS) $^ -o $(TARGET)

$(TARGET): sum.c main.c
	$(CC) $(CFLAGS) $^ -o $@

%.s: %.c
	$(CC) -S -fverbose-asm $(CFLAGS) $< -o $@

clean:
	rm -f *.o *.s