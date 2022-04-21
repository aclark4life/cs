#include <stdio.h>
#include <stdlib.h>

int Factorial(int n) {
  if (n == 1)
    return 1;
  else
    return n * Factorial(n - 1);
  printf("%d", n);
}

int main(int argc, char *argv[]) {
  int n;
  n = atoi(argv[1]);
  Factorial(n);
  printf("ANSWER> %d\n", n);
}
