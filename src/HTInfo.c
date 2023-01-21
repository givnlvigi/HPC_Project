/*
 * TInfo: tipo elementare
 */

#include <stdio.h>
#include <string.h>
#include "HTInfo.h"

int htInfoEqual (HTInfo info1, HTInfo info2) {
    return info1.key == info2.key;
}

int htInfoGreater (HTInfo info1, HTInfo info2) {
    return  info1.key > info2.key;
}

int htInfoLess (HTInfo info1, HTInfo info2) {
    return  info1.key < info2.key;
}

void htInfoPrint (HTInfo info) {
    printf ("(%d: %d) ", info.key, info.value);

    /* con TValue alternativo
    printf ("(%d: %s, %.2f) ", info.key, info.value.name, info.value.price);
    */
}

unsigned int keyHash (HTKey key) {
    return key;
}