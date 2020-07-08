#include <stdio.h>

check(char *argv[]) {
  int i;

  for (i = 0; i < strlen(argv[1]); i++) {
    if (isdigit(argv[1][i]) == 0) {
      printf("%s: not an integer.\n", argv[1]);
      exit(0);
    }
  }
  if (strlen(argv[1]) > 6) {
    printf("%s: too big.\n", argv[1]);
    exit(0);
  }

  for (i = 0; i < strlen(argv[2]); i++) {
    if (isdigit(argv[2][i]) == 0) {
      printf("%s: not an integer.\n", argv[2]);
      exit(0);
    }
  }
  if (strlen(argv[2]) > 6) {
    printf("%s: too big.\n", argv[2]);
    exit(0);
  }

  for (i = 0; i < strlen(argv[3]); i++) {
    if (isdigit(argv[3][i]) == 0) {
      printf("%s: not an integer.\n", argv[3]);
      exit(0);
    }
  }
  if (strlen(argv[3]) > 6) {
    printf("%s: too big.\n", argv[3]);
    exit(0);
  }
}
