#include <stdio.h>

void main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Hello! Please provide a name.\n");
  } else
    printf("Hello, %s!\n", argv[1]);
}
