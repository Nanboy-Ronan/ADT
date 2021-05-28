#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* This defines a simple hash table for string with linear probe */
#define CAPACITY 100000

typedef struct Entry Entry;

typedef struct Table Table;

int hash(const char* key);

Entry* hashEntry(const char* key, const char* value);

Table* hashTableInit();

void hashTableDestory(Table* hashtable);

void hashPut(Table* hashtable, const char* key, const char* value);

char* hashGet(Table* hashtable, const char* key);

oid hashDelete(Table* hashtable, const char *key);