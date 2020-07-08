#include <ctype.h>
#include <stdio.h>

main(int argc, char **argv) {
  int a = '3';
  int b = 'c';

  int c;
  int d;

  if (argc == 1) {
    c = isdigit(a);
    d = isdigit(b);
    printf("%d\n", c);
    printf("%d\n", d);
  }
}
