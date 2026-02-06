#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *infile;

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }

  infile = fopen(argv[1], "r");
  if (infile == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  /* TODO: Add file processing logic here */

  fclose(infile);
  return EXIT_SUCCESS;
}
