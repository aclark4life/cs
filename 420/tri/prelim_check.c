#include <limits.h>
#include <stdio.h>

prelim_check(char *argv[], int n) {
  int i;

  if (strlen(argv[n]) > 10) {
    printf("%s: input error.\n", argv[n]);
    exit(0);
  }

  for (i = 0; i < strlen(argv[n]); i++) {
    if (isdigit(argv[n][i]) == 0) {
      printf("%s: input error.\n", argv[n]);
      exit(0);
    }
  }
}
