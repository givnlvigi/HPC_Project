/*
 * TInfo: tipo elementare
 */

#ifndef HTINFO_H
#define HTINFO_H

typedef int HTKey;
typedef int HTValue;


typedef struct {
    HTKey key;
    HTValue value;
} HTInfo;

int htInfoEqual (HTInfo, HTInfo);
int htInfoGreater (HTInfo, HTInfo);
int htInfoLess (HTInfo, HTInfo);
void htInfoPrint (HTInfo);
unsigned int keyHash (HTKey);

#endif

