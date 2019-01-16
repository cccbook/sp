CC := gcc
AR := ar
CFLAGS = -std=c99 -O0
TARGET = run.o
LIB = libstat.a

all: $(TARGET)

$(TARGET): $(LIB) main.o
	$(CC) $(CFLAGS) $^ -L ./ -lstat -o $@

$(LIB): sum.o
	$(AR) -r $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.a