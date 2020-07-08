#include <stdio.h>

check_triangle(int a, int b, int c) {
  if (((a + b) > c) && ((a + c) > b) && ((c + b) > a)) {
    if ((a == b) && (b == c))
      printf("%d %d %d: equilateral\n", a, b, c);
    if (((a == b) && !(b == c)) || ((b == c) && !(b == a)) ||
        ((a == c) && !(a == b)))
      printf("%d %d %d: isosceles\n", a, b, c);
    if (!(a == b) && !(b == c) && !(a == c))
      printf("%d %d %d: scalene\n", a, b, c);
  } else {
    printf("%d %d %d: not a triangle\n", a, b, c);
  }
}
