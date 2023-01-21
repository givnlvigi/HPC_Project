/*
 * THTopen: hash table a indirizzamento aperto
 */

#ifndef THT_H
#define THT_H
#include "HTInfo.h"

#define MAX_LOAD 0.75
#define GROW_FACTOR 2

typedef struct SHashTable {
    HTInfo *bucket;
    int *used;
    int n_bucket;
    int n_used;
} THT;

THT *HTcreate (int n);
void HTdestroy (THT* ht);
void HTinsert (THT* ht, HTKey key, HTValue value);
void HTdelete (THT* ht, HTKey key);
HTValue *HTsearch (THT* ht, HTKey key);
void HTprint(THT* ht);
void HTprintStructure(THT* ht);

#endif