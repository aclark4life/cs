/* st.c */
#include "stP.h"
#include <stdio.h>
int st_add(tSymbolTable st, void *symbol) {
  if (st->current_scope == -1)
    printf("no open scopes\n");
  else if (st_lookup(st, symbol) != st->current_scope) {
    ht_insert(st->scopes[st->current_scope], symbol);
    return (1);
  }
  return (-1);
}

/* purpose: dump a symbol table
 * input:   a symbol table and a function to print symbols
 * output:  nothing (side effect: the symbol table is printed)
 */
void st_dump(tSymbolTable st, void (*symbol_print)()) {
  int i;
  if (st->current_scope == -1)
    printf("no open scopes\n");
  else {
    for (i = 0; i <= st->current_scope; i++) {
      printf("\n --- scope %d ---\n", i);
      ht_print(st->scopes[i], symbol_print);
    }
  }
}

tSymbolTable st_initialize(int size, int (*symbol_compare_function)(),
                           int (*symbol_hash_function)()) {
  tSymbolTable st;
  st = (tSymbolTable)check_malloc(SYMBOL_TABLE_SIZE);
  st->ht_size = size;
  st->symbol_compare_function = symbol_compare_function;
  st->symbol_hash_function = symbol_hash_function;
  st->current_scope = -1;
}

void st_free(tSymbolTable st) {
  int i;
  for (i = 0; i <= st->current_scope; i++)
    ht_free(st->scopes[i]);

  free(st);
}

int st_lookup(tSymbolTable st, void *symbol) {
  int i;

  for (i = st->current_scope; i >= 0; i--)
    if (ht_lookup(st->scopes[i], symbol))
      return (i);
  return (-1);
}

int st_open_scope(tSymbolTable st) {

  if (st->current_scope < MAX_SCOPES) {
    st->current_scope++;
    st->scopes[st->current_scope] = ht_initialize(
        SCOPE_HT_SIZE, st->symbol_compare_function, st->symbol_hash_function);
    return (1);
  }
  return (-1);
}

int st_close_scope(tSymbolTable st) {
  if (st->current_scope == -1)
    return (-1);
  ht_free(st->scopes[st->current_scope]);
  st->current_scope--;
  return (1);
}
