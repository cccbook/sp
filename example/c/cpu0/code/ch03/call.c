#include <stdio.h>

int main() {
	int x = 1;
	int y;
	y = f1(x);
	printf("y=%d\n", y);
	return 1;
}
int f1(int t) {
	int b = f2(&t);
	return b+b;
}
int f2(int *p) {
	int r= *p+5;
	return r;
}
