CC   = gcc.exe -D__DEBUG__
OBJ  = Parser.o Tree.o Lib.o Scanner.o Array.o Compiler.o HashTable.o Generator.o Assembler.o Cpu0.o OpTable.o
LINKOBJ = $(OBJ)
LIBS = 
INCS = 
BIN  = test.exe c0c.exe as0.exe vm0.exe
CFLAGS = $(INCS) -g3
RM = rm -f

.PHONY: all clean

all: $(OBJ) test c0c as0 vm0

test: $(OBJ)
	$(CC) main.c $(LINKOBJ) -DTARGET=TEST -o test $(LIBS)

c0c: $(OBJ)
	$(CC) main.c $(LINKOBJ) -DTARGET=C0C -o c0c $(LIBS)

as0: $(OBJ)
	$(CC) main.c $(LINKOBJ) -DTARGET=AS0 -o as0 $(LIBS)

vm0: $(OBJ)
	$(CC) main.c $(LINKOBJ) -DTARGET=VM0 -o vm0 $(LIBS)

clean: 
	${RM} $(OBJ) $(BIN)

Parser.o: Parser.c
	$(CC) -c Parser.c -o Parser.o $(CFLAGS)

Tree.o: Tree.c
	$(CC) -c Tree.c -o Tree.o $(CFLAGS)

Lib.o: Lib.c
	$(CC) -c Lib.c -o Lib.o $(CFLAGS)

Scanner.o: Scanner.c
	$(CC) -c Scanner.c -o Scanner.o $(CFLAGS)

Array.o: Array.c
	$(CC) -c Array.c -o Array.o $(CFLAGS)

Compiler.o: Compiler.c
	$(CC) -c Compiler.c -o Compiler.o $(CFLAGS)

HashTable.o: HashTable.c
	$(CC) -c HashTable.c -o HashTable.o $(CFLAGS)

Generator.o: Generator.c
	$(CC) -c Generator.c -o Generator.o $(CFLAGS)

Assembler.o: Assembler.c
	$(CC) -c Assembler.c -o Assembler.o $(CFLAGS)

Cpu0.o: Cpu0.c
	$(CC) -c Cpu0.c -o Cpu0.o $(CFLAGS)

OpTable.o: OpTable.c
	$(CC) -c OpTable.c -o OpTable.o $(CFLAGS)
