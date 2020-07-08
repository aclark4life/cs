#include <stdio.h>

void main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("no, fuck you!\n");
    // printf ( "Sorry, I don't take command line arguments.\n");
  } else
    printf("yeah, fuck %s!\n", argv[1]);
}
