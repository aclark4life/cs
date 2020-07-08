#include <ctype.h>
#include <math.h>
#include <stdio.h>
main(int argc, char *argv[])

{
  FILE *infile;
  char letter, ch;
  float p[26];
  int s[26], a[26], i, j, t, x, sum = 0;
  if (argc == 2) {
    infile = fopen(argv[1], "r");
    if (infile == NULL) {
      printf("Unable to open the input file.\n");
      exit(-1);
    }
  } else {
    printf("usage: %s file\n", argv[0]);
    exit(-1);
  }
  for (i = 0; i < 26; i++) {
    a[i] = 0;
    p[i] = 0;
    s[i] = 0;
  }
  for (; (fscanf(infile, "%c", &letter)) != EOF;) {
    letter = toupper(letter);
    letter = letter - 'A';
    a[letter]++;
  }
  for (i = 0; i < 26; i++)
    sum = sum + a[i];
  for (i = 0; i < 26; i++) {
    s[i] = i + 64;
    s[i]++;
  }
  for (i = 0; i < 26; i++)
    for (j = i + 1; j < 26; j++)
      if (a[i] < a[j]) {
        t = a[i];
        x = s[i];
        a[i] = a[j];
        s[i] = s[j];
        a[j] = t;
        s[j] = x;
      }
  for (i = 0; i < 26; i++)
    p[i] = ((float)a[i] / sum) * 100;
  for (i = 0; i < 26; i++)
    fprintf(stderr, "%c = %5.2f\n", s[i], p[i]);
}
