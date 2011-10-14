/* stP.h */
const int SCOPE_HT_SIZE = 4;
#define MAX_SCOPES 10

/* [why doesn't this work?] const int MAX_SCOPES = 10;*/
#include "../assignment.1/ht.h"

typedef struct sSymbolTable
{
    int current_scope;
    int (*symbol_hash_function)();
    int (*symbol_compare_function)();
    tHashTable scopes[MAX_SCOPES];
    int ht_size;      




} *tSymbolTable;

const int SYMBOL_TABLE_SIZE = sizeof (struct sSymbolTable);
