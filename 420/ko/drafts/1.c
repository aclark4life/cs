#include <stdio.h>
main() {
  FILE *infile;
  char *buf = (char *)malloc(10 * sizeof(char *));

  int i = 0;

  system("ls > foo");
  infile = fopen("foo", "r");

  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
  buf[i] = fgetc(infile);
  printf("%c", buf[i]);
}
