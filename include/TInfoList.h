/*
 * TInfoList: tipo elementare
 */


#ifndef TINFOLIST_H
#define TINFOLIST_H

typedef int TKey;
typedef int TValue;

struct SInfoList {
    TKey key;
    TValue value;
};
typedef struct SInfoList TInfoList;

TInfoList infoListCreateKey(TKey key);
TInfoList infoListCreate(TKey, TValue);
int infoListEqual (TInfoList, TInfoList);
int infoListGreater (TInfoList, TInfoList);
int infoListLess (TInfoList, TInfoList);
void infoListPrint (TInfoList);

#endif /* TINFOLIST_H */


