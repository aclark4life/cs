/* ht.c */

static char *cr = "copyright (c) David Binkley 1993";

#include "htP.h"
#include "util.h"
#include <stdio.h>

/* purpose: delete an entry from a hash table
 * input:   a hash table and a entry, n
 * output:  nothing (side effect: the updated hashtable)
 */
void ht_delete(ht, n) tHashTable ht;
void *n;
{
  tBucket *tmp, *last;
  int hash_value;

  hash_value = abs((*ht->hash)(n)) % ht->size;

  for (tmp = ht->table[hash_value], last = tmp; tmp != NULL;
       last = tmp, tmp = tmp->next)
    if ((*ht->compare)(tmp->data, n)) {
      break;
    }
  if (tmp != NULL) {
    if (tmp == last) {
      ht->table[hash_value] = tmp->next;
    } else {
      last->next = tmp->next;
    }
    free(tmp);
  }
}

/* purpose:
 * input:
 * output:
 */
void ht_free(ht) tHashTable ht;
{

  tBucket *tmp;
  tBucket *extra;
  int i;

  for (i = 0; i < ht->size; i++) {
    for (tmp = ht->table[i]; tmp != NULL; tmp = extra) {
      extra = tmp->next;
      free(tmp);
    }
  }
  free(ht);
}

/* purpose:
 * input:
 * output:
 */
tHashTable ht_initialize(size, compare_function, hash_function) int size;
int (*compare_function)(), (*hash_function)();
{
  int i;
  tHashTable ht;

  ht = (tHashTable)check_malloc(HASHTABLE_SIZE);
  ht->size = size;
  ht->compare = compare_function;
  ht->hash = hash_function;
  ht->table = (tBucket **)check_malloc(size * sizeof(tBucket *));

  for (i = 0; i < ht->size; i++)
    ht->table[i] = NULL;

  return (ht);
}

/* purpose:
 * input:
 * output:
 */
void ht_insert(ht, n) tHashTable ht;
void *n;
{

  tBucket *new;
  int hash_value;
  hash_value = abs((*ht->hash)(n)) % ht->size;

  new = (tBucket *)check_malloc(BUCKET_SIZE);
  new->data = n;
  new->next = ht->table[hash_value];
  ht->table[hash_value] = new;
}

/* purpose:
 * input:
 * output:
 */
void *ht_lookup(ht, n) tHashTable ht;
void *n;
{
  tBucket *tmp;
  int hash_value;

  hash_value = abs((*ht->hash)(n)) % ht->size;

  for (tmp = ht->table[hash_value]; tmp != NULL; tmp = tmp->next)
    if ((*ht->compare)(tmp->data, n))
      return (tmp->data);

  return (NULL);
}

/* purpose:
 * input:
 * output:
 */
void ht_print(ht, print_function) tHashTable ht;
void (*print_function)();
{
  int i;
  tBucket *tmp;

  for (i = 0; i < ht->size; i++) {
    printf("Bucket %d: ", i);
    for (tmp = ht->table[i]; tmp != NULL; tmp = tmp->next)
      (*print_function)(tmp->data);
    printf("\n");
  }
}
