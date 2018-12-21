int strcopy(char *t, char *s, int len, int scale) {
  int  i = 0;
  char temp[50];
  char c = ' ';
  char end = '\0';
  int  x = 1, y = 2, z = 3, w = 4, k = 5, l = 6, m=7;
  while (i < len && *s != end) {
    c = *t;
    *s = c;
    s++;
    t++;
    i++;
    // temp[i] = *t;
  }
  *s = end;
  return i * scale * x;
}

char *c = "global constant";

int main() {
  char *a = "hello! how are you ?";
  int len=10, scale=4;
  strcopy(a, c, len, scale);
}

