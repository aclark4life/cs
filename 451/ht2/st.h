/* st.h */
#include "../assignment.1/ht.h"

typedef void * tSymbolTable;
void         st_add(tSymbolTable st, void *symbol);
int          st_close_scope(tSymbolTable st);
void         st_dump(tSymbolTable st, void (*symbol_print)());
void         st_free(tSymbolTable st);
tSymbolTable st_initialize(int size, 
			   int (*symbol_compare_function)(), 
			   int (*symbol_hash_funcion)());
int          st_lookup(tSymbolTable st, void *symbol);
int          st_open_scope(tSymbolTable st);

