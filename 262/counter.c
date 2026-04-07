#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *infile;
  char letter;
  float percentages[26];
  int char_codes[26], counts[26], i, j, temp_count, temp_char, sum = 0;
  if (argc == 2) {
    infile = fopen(argv[1], "r");
    if (infile == NULL) {
      printf("Unable to open the input file.\n");
      exit(EXIT_FAILURE);
    }
  } else {
    printf("usage: %s file\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < 26; i++) {
    counts[i] = 0;
    percentages[i] = 0;
    char_codes[i] = 0;
  }
  for (; (fscanf(infile, "%c", &letter)) != EOF;) {
    letter = toupper(letter);
    letter = letter - 'A';
    counts[(unsigned char)letter]++;
  }
  for (i = 0; i < 26; i++)
    sum = sum + counts[i];
  for (i = 0; i < 26; i++) {
    char_codes[i] = i + 64;
    char_codes[i]++;
  }
  for (i = 0; i < 26; i++)
    for (j = i + 1; j < 26; j++)
      if (counts[i] < counts[j]) {
        temp_count = counts[i];
        temp_char = char_codes[i];
        counts[i] = counts[j];
        char_codes[i] = char_codes[j];
        counts[j] = temp_count;
        char_codes[j] = temp_char;
      }
  for (i = 0; i < 26; i++)
    percentages[i] = ((float)counts[i] / sum) * 100;
  for (i = 0; i < 26; i++)
    fprintf(stderr, "%c = %5.2f\n", char_codes[i], percentages[i]);
}
