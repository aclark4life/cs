#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *infile1;
  FILE *infile2;
  FILE *outfile;

  int i, j, k, l;

  if (argc != 4) {
    printf("usage: %s file1 file2 file3\n", argv[0]);
    exit(0);
  }
  infile1 = fopen(argv[1], "r");
  if (infile1 == NULL) {
    printf("Unable to open the input file.\n");
    exit(0);
  }
  infile2 = fopen(argv[2], "r");
  if (infile2 == NULL) {
    printf("Unable to open the input file.\n");
    exit(0);
  }
  outfile = fopen(argv[3], "w");

  fscanf(infile1, "%d", &i);
  fscanf(infile2, "%d", &j);

  while ((feof(infile1) != 1) && (feof(infile2) != 1)) {

    if (i <= j) {
      fprintf(outfile, "%d\n", i);
      fscanf(infile1, "%d", &i);
    } else {
      fprintf(outfile, "%d\n", j);
      fscanf(infile2, "%d", &j);
    }

    if (feof(infile1)) {
      fprintf(outfile, "%d\n", j);
    }
    if (feof(infile2)) {
      fprintf(outfile, "%d\n", i);
    }
  }
  for (; (fscanf(infile1, "%d", &i)) != EOF;)
    fprintf(outfile, "%d\n", i);
  for (; (fscanf(infile2, "%d", &j)) != EOF;)
    fprintf(outfile, "%d\n", j);

  fclose(infile1);
  fclose(infile2);
  fclose(outfile);
}
