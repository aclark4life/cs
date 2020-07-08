#include <stdio.h>
#include <stdlib.h>

call_malloc()

{
  int *x;
  x = (int *)malloc(sizeof(int));
}

main(int argc, char *argv) {
  int i;

  for (i = 0; i < 1000000; i++) {
    call_malloc();
  }
}
