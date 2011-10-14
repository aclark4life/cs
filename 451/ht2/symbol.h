/* symbol.h */

#define VARIABLE_KIND  1
#define TYPE_KIND 2
#define TAG_KIND 3

#ifndef SYMBOL_PROTOTYPESONLY
typedef void *tSymbol;
#endif

int     symbol_compare(tSymbol s1, tSymbol s2);
void    symbol_free(tSymbol s);
int     symbol_hash(tSymbol s);
tSymbol symbol_initialize(char *text, int kind);
void    symbol_print(tSymbol s);
