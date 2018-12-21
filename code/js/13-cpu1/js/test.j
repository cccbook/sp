s = sum(10);
m = max(3,5);

function sum(n) {
  s = 0;
  i=1;
  while (i<=10) {
    s = s + i;
    i++;
  }
  return s;
}

function max(a, b) {
  if (a > b)
    return a;
  else
    return b;
}

function total(a) {
  s = 0;
  for (i in a) {
    s = s + a[i];
  }
  return s;
}

a = [ 1, 3, 7, 2, 6];
t = total(a);
word = { e:"dog", c:"狗" };
