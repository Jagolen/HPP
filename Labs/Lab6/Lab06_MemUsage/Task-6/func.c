#include "func.h"

static int function_call_counter = 0;

int f(int k) {
  // Increment function call counter
  function_call_counter++;
  // Do some expensive operations so that this function takes some time
  int x = 3;
  if(k > 0 && 88/k > 2)
    x += 11;
  if(k > 0)
    x += 777/k + 888 / k + 999 / k;
  return x;
}

int get_counter() {
  return function_call_counter;
}

