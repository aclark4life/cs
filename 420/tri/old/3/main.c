#include <stdio.h>

main(int argc, char **argv) {
  int a, b, c;

  /*#define INT_MIN         (-2147483647-1)
    #define INT_MAX         2147483647
  1. make sure all command line entries are digits
  2. make sure digits are a triangle
          ie. the sum of two sides is greater than the third
  3. make sure that digits don't exceed boundaries
  4. write atoi < check MAX_INT; reject negatives
  */
  if (argc == 4) {
    if ((a = atoi(argv[1])) == 0) {
      printf("%s: not a digit\n", argv[1]);
      exit(0);
    }
    if ((b = atoi(argv[2])) == 0) {
      printf("%s: not a digit\n", argv[2]);
      exit(0);
    }
    if ((c = atoi(argv[3])) == 0) {
      printf("%s: not a digit\n", argv[3]);
      exit(0);
    }
    what_kind(a, b, c);
  } else {
    printf("usage: side1 side2 side3\n");
    exit(0);
  }
}
