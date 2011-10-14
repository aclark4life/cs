/* ht.h */

/* copyright (c) David Binkley 1993 */

#ifndef _HT
#define _HT

#ifndef _HT_PROTOTYPES_ONLY
typedef void *tHashTable;
#endif

/* exported functions */

tHashTable ht_initialize(int, int (*compare_function)(),int(*hash_function)());
void       ht_free(tHashTable);
void       ht_insert(tHashTable, void*);
void       ht_delete(tHashTable, void*);
void      *ht_lookup(tHashTable, void*);

/* for debugging */
void       ht_print(tHashTable, void (*print_function)());

#endif
