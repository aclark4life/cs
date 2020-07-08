#include <limits.h>
#include <stdio.h>

/* #define INT_MAX         2147483647 */   /* max value of an "int" */
/* #define ULONG_MAX       4294967295UL */ /* max value of "unsigned long int"
                                            */

unsigned long int my_atoi(char *argv[], int n) {
  unsigned long int conv_int = 0;
  int i;

  for (i = 0; i < (strlen(argv[n])); i++) {
    conv_int = (conv_int * 10) + (argv[n][i]) - '0';
  }
  if (conv_int <= INT_MAX)
    return (conv_int);
  else {
    printf("%s: input error\n", argv[n]);
    exit(0);
  }
}
