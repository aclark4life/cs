#include <stdio.h>
#define NUM 10
main() {
  FILE *infile;
  char *buf = (char *)malloc(NUM * sizeof(char *));

  int i = 0;

  system("ls > foo");
  infile = fopen("foo", "r");

  fgets(buf, NUM, infile);
  for (i = 0; i < NUM; i++) {
    printf("%c\n", buf[i]);
  }
}
