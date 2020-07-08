#include "htP.h"
#include "util.h"
#include <stdio.h>

/*  purpose: to delete an entry from a hash table
 *  input: a hash table and an entry, n
 *  output: nothing (side effect: the updated hashtable)
 */

void ht_delete(ht, n) tHashTable ht;
void *n;
{
  tBucket *tmp, *last;
  int hash_value;

  hash_value = abs((*ht->hash)(n)) % ht->size;

        eor(tmp = ht->table[hash_value
