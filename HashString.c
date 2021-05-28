#include "HashString.h"

typedef struct Entry{
    char *key;
    char *value;
    Table *next;
} Entry;

typedef struct Table{
    Entry **entries;
}Table;

int hash(const char* key){
    int value = 0;
    int lenth = strlen(key);

    for(int i = 0; i < lenth; ++i){
        value = 2 * value + key[i];
    }

    value = value % CAPACITY;

    return value;
}

Entry* hashEntry(const char* key, const char* value){
    Entry* entry = malloc(sizeof(Entry));
    entry->key = malloc(strlen(key) + 1);
    entry->value = malloc(strlen(value) + 1);

    strcpy(entry->key, key);
    strcpy(entry->value, value);
    entry->next = NULL;

    return entry;
}

Table* hashTableInit(){
    Table* hashTable = malloc(sizeof(Table));
    hashTable->entries = malloc(CAPACITY*sizeof(Entry*));

    for(int i = 0; i < CAPACITY; i++){
        hashTable->entries[i] = NULL;
    }

    return hashTable;
}

void hashTableDestory(Table* hashtable){
    for(int i = 0; i < CAPACITY; i++){
        if(hashtable->entries[i] != NULL){
            free(hashtable->entries[i]->key);
            free(hashtable->entries[i]->value);
            hashtable->entries[i]->next = NULL;
            free(hashtable->entries[i]);
        }
    }
    free(hashtable->entries);
    free(hashtable);

}

void hashPut(Table* hashtable, const char* key, const char* value){
    int slot = hash(key);

    Entry* entry = hashtable->entries[slot];

    if(entry == NULL){
        hashtable->entries[slot] = hashEntry(key, value);
        return;
    }

    Entry* prev;

    while(entry != NULL){
        if(strcmp(entry->key, key) == 0){
            free(entry->value);
            entry->value = malloc(strlen(value) + 1);
            strcpy(entry->value, value);
            return;
        }

        prev = entry;
        entry = entry->next;
    }

    prev->next = hashEntry(key, value);
}

char* hashGet(Table* hashtable, const char* key){
    int slot = hash(key);

    Entry* entry = hashtable->entries[slot];

    if(entry == NULL) return NULL;

    while(entry != NULL){
        if(strcmp(entry->key, key) == 0) return entry->value;

        entry = entry->next;
    }

    return NULL;
}

void hashDelete(Table* hashtable, const char *key){
    int slot = hash(key);

    Entry* entry = hashtable->entries[slot];

    if(entry == NULL) return;

    Entry* prev;
    int index = 0;

    while(entry != NULL){
        if(strcmp(entry->key, key) == 0){
            if(entry->next == NULL && index == 0) hashtable->entries[slot] = NULL;
            if(entry->next != NULL && index == 0) hashtable->entries[slot] = entry->next;
            if(entry->next == NULL && index != 0) prev->next = NULL;
            if(entry->next != NULL && index != 0) prev->next = entry->next;

            free(entry->key);
            free(entry->value);
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
        index++;
    }
}

void hashPrint(Table *hashtable) {
    for (int i = 0; i < CAPACITY; ++i) {
        Entry *entry = hashtable->entries[i];

        if (entry == NULL) {
            continue;
        }

        printf("slot[%4d]: ", i);

        for(;;) {
            printf("%s=%s ", entry->key, entry->value);

            if (entry->next == NULL) {
                break;
            }

            entry = entry->next;
        }

        printf("\n");
    }
}

int main(){
    // printf("%d\n", hash("em"));
    // printf("%d\n", hash("russian"));
    // printf("%d\n", hash("pizza"));
    // printf("%d\n", hash("doge"));
    // printf("%d\n", hash("pyro"));
    // printf("%d\n", hash("joost"));
    // printf("%d\n", hash("kalix"));
    // printf("%d\n", hash("kalix"));
    Table* table = hashTableInit();
    hashPut(table, "name1", "em");
    hashPut(table, "name2", "russian");
    hashPut(table, "name3", "pizza");
    hashPut(table, "name4", "doge");
    hashPut(table, "name5", "pyro");
    hashPut(table, "name6", "joost");
    hashPut(table, "name7", "kalix");

    hashTableDestory(table);
    //ht_dump(table);
}
