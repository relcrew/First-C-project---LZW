#ifndef ENCODE_H
#define ENCODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DICT_SIZE 1000000
#define CLEAR_CODE 256
#define END_CODE 257

typedef struct {
    char* key;
    int value;
} Entry;

typedef struct {
    Entry** entries;
    int size;
} HashTable;

void encoder(char*path);


#endif