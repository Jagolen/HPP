#include <stdio.h>

double global1 = 55.5;
double global2 = 66.6;

int gg(int a) {
  int p = 55;
  int q = 66;
  int r = p + a;
  r += q;
  char c;
  for(c = 0; c<100; c++) {
    r += 5;
    if(r == q)
      r--;
  }
  return r;
}

int hh(int a) {
  int i;
  int s = 1;
  for(i = 0; i < a/3; i++) {
    s *= 3;
    s /= 2;
  }
  return s;
}

int ff() {
  int sum = 0;
  int k;
  for(k = 0; k < 33; k++) {
    global1 += 0.1;
    global2 += 0.2;
    int m = k*2;
    sum += gg(m);
    sum += hh(m);
  }
  return sum;
}

int main() {
  int x = ff();
  printf("x = %d\n", x);
  return 0;
}
