
/*-*-c-*-*/
/*
// Gwennie Furr
// Alex Clark
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

extern "C" yylex();  // yylex() was complied in C

main()
{
    int total = 0;
    char *t;

    t = (char *)yylex();
    while (t != NULL)
      {
          printf("%s\n", t);
          t = (char *)yylex();
      }
    return 0;
}


