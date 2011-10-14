/* main.c */
#include <stdio.h>
#include "ht.h"
#include "util.h"

typedef struct sData
{
    int key;
    char name[10];
    int size;
} *tData;
#define DATA_SIZE (sizeof(struct sData))

const int HT_SIZE = 5;

main()
{
    char command;
    tData item;
    tHashTable ht;
    int data_compare(), 
        data_hash();
    void data_print();
    char *check_malloc() ;


    ht = ht_initialize (HT_SIZE, data_compare, data_hash);
    item = (tData) check_malloc(DATA_SIZE);

    while ((command = getchar()) != EOF)
    {
        if (command == 'i' || command == 'd' || command == 'l') 
            scanf("%d", &item->key);

        switch (command)
        {
            case 'i':    ht_insert(ht, item);
                         item = (tData) check_malloc(sizeof (DATA_SIZE));
                         break;

            case 'd':    ht_delete(ht, item);
                         break;

            case 'l':    if (ht_lookup(ht, item) != NULL)
                              printf("Found\n") ;
                         else
                              printf("Not Found\n") ;
                         break;

            case 'p':    ht_print(ht, data_print);
                         break;

            case 'q':    ht_free(ht);
                         exit(0);
        }
    }
}


int data_compare(a, b)
tData a, b ;
{
    return (a->key == b->key);
}


int data_hash(d)
tData d;
{
    return (d->key );
}


void data_print(d)
tData d ;
{
    printf("%d ", d->key) ;
}
