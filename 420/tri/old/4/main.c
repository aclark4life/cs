#include <stdio.h>
#include <strings.h>
main(int argc, char *argv[]) {
  int a, b, c, d, i;
  if (argc == 4) {
    for (i = 0; i < strlen(argv[1]); i++) {
      if (isdigit(argv[1][i]) == 0) {
        printf("%s: not an integer.\n", argv[1]);
        exit(0);
      }
      if (strlen(argv[1]) > 6) {
        printf("%s: too big.\n", argv[1]);
        exit(0);
      }
    }
    for (i = 0; i < strlen(argv[2]); i++) {
      if (isdigit(argv[2][i]) == 0) {
        printf("%s: not an integer.\n", argv[2]);
        exit(0);
      }
      if (strlen(argv[2]) > 6) {
        printf("%s: too big.\n", argv[2]);
        exit(0);
      }
    }
    for (i = 0; i < strlen(argv[3]); i++) {
      if (isdigit(argv[3][i]) == 0) {
        printf("%s: not an integer.\n", argv[3]);
        exit(0);
      }
      if (strlen(argv[3]) > 6) {
        printf("%s: too big.\n", argv[3]);
        exit(0);
      }
    }
    a = atoi(argv[1]);
    b = atoi(argv[2]);
    c = atoi(argv[3]);
    check_triangle(a, b, c);
  } else {
    printf("%s: usage: side1 side2 side3\n", argv[0]);
  }
}
