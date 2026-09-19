#include <stdio.h>
#include <stdlib.h>

call_alloca()

{
  int *x;
  x = (int *)alloca(sizeof(int));
}

main(int argc, char *argv) {
  int i;

  for (i = 0; i < 1000000; i++) {
    call_alloca();
  }
}
