# 1 "macroDebug.c"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "macroDebug.c"

 int bugs = 0;






int main() {
  int x = (3>5?3:5);
  int y = (3<5?3:5);
  printf("max(3,5)=%d\n",x);
  printf("min(3,5)=%d\n",y);

  if (x!=5)
    {printf("max(3,5)");bugs++;};
  if (y!=3)
    {printf("min(3,5)");bugs++;};
  printf("¦@¦³%d­Ó¿ù»~",bugs);

}
