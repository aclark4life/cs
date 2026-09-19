#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OUTFILE_DIR "."

/*#define    L_tmpnam        25     */ /* (sizeof(P_tmpdir) + 15) */

int main(int argc, char *argv[]) {
  FILE *infile;
  FILE *outfile;
  int i = 0;
  int j;
  int fd;
  char s[] = OUTFILE_DIR "/tmpXXXXXX"; /* mkstemp template */

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

  fd = mkstemp(s);
  outfile = fdopen(fd, "w");
  for (; (fscanf(infile, "%d", &j)) != EOF;) {

    if (i >= j) {
      fclose(outfile);
      strcpy(s, OUTFILE_DIR "/tmpXXXXXX");
      fd = mkstemp(s);
      outfile = fdopen(fd, "w");
    }

    fprintf(outfile, "%d\n", j);
    i = j;
  }
}
