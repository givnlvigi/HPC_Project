
#include <stdio.h>
#include "TInfoList.h"

TInfoList infoListCreateKey(TKey key) {
    TInfoList info;
    info.key = key;

    return info;
}

TInfoList infoListCreate(TKey key, TValue value) {
    TInfoList info;
    info.key = key;
    info.value = value;

    return info;
}

int infoListEqual(TInfoList info1, TInfoList info2) {
    return info1.key == info2.key;
}

int infoListGreater(TInfoList info1, TInfoList info2) {
    return info1.key > info2.key;
}

int infoListLess(TInfoList info1, TInfoList info2) {
    return info1.key < info2.key;
}

void infoListPrint(TInfoList info) {
    printf("%d ", info.key);
}
