#include "HashInteger.h"

typedef struct Data{
    int key;
    int value;
} Data;

int capacity = 1000;

int hash(int key){
    return key % capacity;
}

void HashTableInit(){
    
}
