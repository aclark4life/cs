

#include <stdio.h>

main(int argc, char *argv[])

{
  FILE *infile;
  int j;

  infile = stdin;
  printf("Input from stdin.\n");

  scanf(*infile);

  /* for (; (fscanf (infile, "%d", &j))!= EOF ;)
     printf("%d\n", j);
  */
}
