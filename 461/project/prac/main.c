
/*-*-c-*-*/
/*
// Gwennie Furr
// Alex Clark
*/

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" yylex(); // yylex() was complied in C

main() {
  int total = 0;
  char *t;

  t = (char *)yylex();
  while (t != NULL) {
    printf("%s\n", t);
    t = (char *)yylex();
  }
  return 0;
}
