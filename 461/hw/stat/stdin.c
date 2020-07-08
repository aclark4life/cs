

#include <stdio.h>

main(int argc, char *argv[])

{
  FILE *infile;
  char j;

  if (argc == 2) {
    infile = fopen(argv[1], "r");
    if (infile == NULL) {
      printf("Unable to open the input file.\n");
      exit(-1);
    } else {
      printf("input from %s\n", argv[1]);
    }
  } else {
    infile = stdin;
    printf("Input from stdin.\n");
  }

  for (; (fscanf(infile, "%d", &j)) != EOF;)
    printf("%d\n", j);
}
