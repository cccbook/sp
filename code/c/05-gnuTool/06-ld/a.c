extern int shared;

extern void swap(int *a, int *b);

int main() {
  int a = 100;
  swap(&a, &shared);
}
