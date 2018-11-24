extern int stack[];
extern int top;

void push(int x) {
  stack[top++] = x;
}

int pop() {
  return stack[--top];
}
