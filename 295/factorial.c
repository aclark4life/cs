#include <stdio.h>
#include <stdlib.h>

int Factorial(int n) {
  if (n <= 0)
    return 1;
  else if (n == 1)
    return 1;
  else
    return n * Factorial(n - 1);
}

int main(int argc, char *argv[]) {
  int n, result;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <number>\n", argv[0]);
    return EXIT_FAILURE;
  }

  n = atoi(argv[1]);
  result = Factorial(n);
  printf("ANSWER> %d\n", result);

  return EXIT_SUCCESS;
}
