int total(int *a, int size) {
  int s = 0, i = 0;
  while (i < size) {
    s = s + a[i];
  }
  return s;
}

