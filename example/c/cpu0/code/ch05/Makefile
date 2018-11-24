CC = gcc
AR = ar
OBJS = StackType.o StackFunc.o
BIN = stack
RM = rm -f
INCS = -I .
LIBS = -L .
CFLAGS = $(INCS) $(LIBS)

all: $(BIN)

clean: 
	${RM} *.o *.exe *.a

$(BIN): $(AR)
	$(CC) StackMain.c -lstack -o $(BIN) $(CFLAGS)

$(AR) : $(OBJS)
	$(AR) -r libstack.a $(OBJS)

StackFunc.o : StackFunc.c
	$(CC) -c StackFunc.c -o StackFunc.o $(CFLAGS)

StackType.o : StackType.c
	$(CC) -c StackType.c -o StackType.o $(CFLAGS)
