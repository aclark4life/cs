#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  float a, b, c, x;
  float lower_bound, upper_bound, left_height, right_height;
  float base, oldtrap, newtrap, answer, distance;
  int count, number;

  if (argc != 7) {
    printf("usage: %s a b c base1 base2 x\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  a = atof(argv[1]);
  b = atof(argv[2]);
  c = atof(argv[3]);
  lower_bound = atof(argv[4]);
  upper_bound = atof(argv[5]);
  number = atof(argv[6]);

  distance = upper_bound - lower_bound;
  base = distance / number;
  oldtrap = 0;
  for (count = 0; count < number; count++) {
    x = lower_bound;

    left_height = a * pow(x, 2) + b * x + c;
    x = lower_bound + base;
    right_height = a * pow(x, 2) + b * x + c;
    lower_bound = x;
    newtrap = (distance) / number * (left_height + right_height) / 2;
    answer = newtrap + oldtrap;
    oldtrap = answer;
  }
  printf("AREA OF TRAPEZOID: ");
  printf("%f\n", answer);
  exit(0);
}
