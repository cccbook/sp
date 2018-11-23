#include "rlib.h"

void E();
void T();
void F();

// === EBNF Grammar =====
// E=T ([+-] T)*
// T=F ([*/] F)?
// T=[0-9] | (E)

int main(int argc, char * argv[]) {
	E();
	int i;
	for (i=0; i<10; i++) {
		E();
		printf("\n");
	}
}

void E() {
    T();
	while (randInt(10) < 3) {
       printf("%c", randChar("+-"));
	   T();
	}
}

void T() {
    F();
	if (randInt(10) < 7) {
		printf("%c", randChar("*/"));
		F();
	}
}

void F() {
    if (randInt(10) < 8) {
		printf("%c", randChar("0123456789"));
	} else {
		printf("(");
		E();
		printf(")");
	}
}
