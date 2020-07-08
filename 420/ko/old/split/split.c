#include <stdio.h>
#define TMP_DIR "/home/aclark/indep_study/ko/tmp"

main(int argc, char *argv[]) {
  FILE *infile;
  FILE *outfile;
  int i = 0;
  int j;
  char s[L_tmpnam]; /* (sizeof(P_tmpdir) + 15) */

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
  outfile = fopen(tempnam(TMP_DIR, s), "w");
  for (; (fscanf(infile, "%d", &j)) != EOF;) {
    if (i >= j) {
      fclose(outfile);
      outfile = fopen(tempnam(TMP_DIR, s), "w");
    }
    fprintf(outfile, "%d\n", j);
    i = j;
  }
}
