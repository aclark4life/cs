/* htP.h */

/* copyright (c) David Binkley 1993,96 */

/* the type for a bucket in a hash table */
typedef struct sBucket
{
    struct sBucket *next;
    void *data;
} tBucket;

#define BUCKET_SIZE (sizeof(struct sBucket))







/* the type for a hash table */
typedef struct sHashTable
{
    int size;
    int	(*compare)(), (*hash)() ;
    tBucket **table;
    /* tBucket *table[]; */
} *tHashTable;

#define HASHTABLE_SIZE (sizeof(struct sHashTable))





/* exported functions */

tHashTable ht_initialize(int, int (*compare_function)(),int(*hash_function)());
void       ht_free(tHashTable);
void       ht_insert(tHashTable, void*);
void       ht_delete(tHashTable, void*);
void      *ht_lookup(tHashTable, void*);

/* for debugging */
void       ht_print(tHashTable, void (*print_function)());

