/*symbol.c*/
/*aclark*/

#include "symbolP.h"
#include "util.h"
#include <stdio.h>

int symbol_compare(tSymbol s1, tSymbol s2) { /* strcmp the names */
  return (!strcmp(s1->name, s2->name));
}

void symbol_free(tSymbol s) {
  free(s->name);
  free(s);
}

int symbol_hash(tSymbol s) {
  /* count the letters in name and make each number a hash_value */
  /* return an int */
  /* or, how about just return the first char in name */

  return (s->name[0]);
}

tSymbol symbol_initialize(char *text, int kind) {

  /* malloc a symbol */
  /* string_copy */
  /* set name = to string copy of text */
  tSymbol symbol;

  symbol = (tSymbol)check_malloc(SYMBOL_SIZE);
  symbol->name = string_copy(text);
  symbol->kind = kind;
}

void symbol_print(tSymbol s) {

  /* print whatever i want */
  printf(" %s", s->name);
}
