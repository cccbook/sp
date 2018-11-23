#include <stdio.h>
#include <assert.h>
#include <string.h>

void parse(char *str);
void push(char c);
char pop(char c);
char ch();
char next();
int isNext(char *set);
int nextTemp();
int E();
int T();
int F();

int main(int argc, char * argv[]) {
    printf("=== EBNF Grammar =====\n");
    printf("E=T ([+-] T)*\n");
    printf("T=F ([*/] F)*\n");
    printf("F=N | '(' E ')'\n");
    printf("==== parse:%s ========\n", argv[1]);
    parse(argv[1]);
}

int tokenIdx = 0;
char *tokens;

void parse(char *str) {
     tokens = str;
     E();
}

char stack[100];
int top = 0;

void push(char c) {
  stack[top++] = c;
}

char pop(char c) {
  char ctop = stack[--top];
  assert(ctop==c);
  return ctop;
}

char ch() {
  char c = tokens[tokenIdx];
  return c;
}

char next() {
  char c = ch();
  tokenIdx++;
  return c;
}

int isNext(char *set) {
  return (ch()!='\0' && strchr(set, ch())!=NULL);
}

int tempIdx = 0;
int nextTemp() {
    return tempIdx++;
}

// E = T ([+-] T)*
int E() {
    push('E');
    int i1 = T();
    while (isNext("+-")) {
          char op=next();
          int i2 = T();
          int i = nextTemp();
          printf("t%d=t%d%ct%d\n", i, i1, op, i2);
          i1 = i;
    }
    pop('E');
    return i1;
}

// T = F ([*/] F)*
int T() {
    push('T');
    int f1 = F();
    while (isNext("*/")) {
          char op=next();
          int f2 = F();
          int f = nextTemp();
          printf("t%d=t%d%ct%d\n", f, f1, op, f2);
          f1 = f;
    }
    pop('T');
    return f1;
}

// F = N | '(' E ')'
int F() {
    int f;
    push('F');
    if (ch()=='(') {
      next();
      f = E();
      assert(ch()==')');
      next();
    } else {
      assert(ch()>='0' && ch()<='9');
      f = nextTemp();
      char c=next();
      printf("t%d=%c\n", f, c);
    }
    pop('F');
    return f; 
}
