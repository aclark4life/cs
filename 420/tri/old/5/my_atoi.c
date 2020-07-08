#include <stdio.h>

unsigned long int my_atoi(char *argv[], int n) {
  unsigned long int conv_int = 0;
  int i;
  int temp[10];
  char a = '0';

  for (i = 0; i < (strlen(argv[n])); i++) {
    temp[i] = ((argv[n][i]) - a);
    if (conv_int == 0)
      conv_int = (temp[i]);
    else
      conv_int = (conv_int * 10) + temp[i];
  }
  return (conv_int);
}
