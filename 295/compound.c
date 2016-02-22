#include <stdio.h>

float amount(int t) {
  float answer;
  if (t == 0)
    return 1000;
  else {
    answer = amount(t - 1);
    answer = answer * 1.055;
    return answer;
  }
}

main(int argc, char *argv[]) {
  int t = 0;
  int i = 0;
  if (argc != 2)
    exit(-1);
  else {
    t = atoi(argv[1]);
    printf("amount: %1.2f\n", amount(t));
  }
}
