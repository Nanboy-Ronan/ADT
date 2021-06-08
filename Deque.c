#include "Deque.h"

typedef struct  Deque{
    ElementType* a; // array
    int front;
    int rear;
    int numOfElements;
    int capacity;
}Deque;

Deque* DequeInit(){
    Deque* deque = malloc(sizeof(Deque));
    deque->a = malloc(sizeof(ElementType)*10);
    deque->front = -1;
    deque->rear = -1;
    deque->numOfElements = 0;
    deque->capacity = 10;
}

void DequeDestroy(Deque* deque){
    free(deque->a);
    free(deque);
}

void resizeUp(Deque* deque){
    if(deque->numOfElements == deque->capacity){
        ElementType* a = malloc(2*deque->capacity*sizeof(ElementType));
        if(deque->front < deque->rear){
            int index = 0;
            for(int i = deque->front; i <= deque->rear; i++){
                a[index] = deque->a[i];
                index++;
            }
        }else{
            int index = 0;
            for(int i = deque->front; i <= deque->numOfElements - 1; i++){
                a[index] = deque->a[i];
                index++;
            }
            for(int i = 0; i <= deque->rear; i++){
                a[index] = deque->a[i];
                index++;
            }
        }
        free(deque->a);
        deque->a = a;
        deque->front = 0;
        deque->rear = deque->numOfElements - 1;
        deque->capacity *= 2;
    }
}


void resizeDown(Deque* deque){
    if(deque->numOfElements < 0.25*deque->capacity){
        int size = ceil(0.25*deque->capacity);
        ElementType* a = malloc(size*sizeof(ElementType));
        if(deque->front <= deque->rear){
            int index = 0;
            for(int i = deque->front; i <= deque->rear; i++){
                a[index] = deque->a[i];
                index++;
            }
        }else{
            int index = 0;
            for(int i = deque->front; i <= deque->numOfElements - 1; i++){
                a[index] = deque->a[i];
                index++;
            }
            for(int i = 0; i <= deque->rear; i++){
                a[index] = deque->a[i];
                index++;
            }
        }
        free(deque->a);
        deque->a = a;
        deque->front = 0;
        deque->rear = deque->numOfElements - 1;
        deque->capacity = size;

    }
}


void pushRight(Deque* deque, ElementType ele){
    assert(deque);
    /* if full then resize my multiply a constant */
    if(deque->numOfElements == deque->capacity) resizeUp(deque);

    if(deque->front == -1 && deque->rear == -1){
        deque->front = 0;
        deque->rear = 0;
    }else{
        deque->rear = (deque->rear + 1) % deque->capacity;
    }
    deque->a[deque->rear] = ele;
    deque->numOfElements++;
}

void pushLeft(Deque* deque, ElementType ele){
    assert(deque);
    /* if full then resize my multiply a constant */
    if(deque->numOfElements == deque->capacity) resizeUp(deque);

    if(deque->front == -1 && deque->rear == -1){
        deque->front = 0;
        deque->rear = 0;
    }else{
        if(deque->front - 1 < 0){
            deque->front = deque->capacity + (deque->front - 1);
        }else{
            deque->front = (deque->front - 1) % deque->capacity;
        }
    }
    deque->a[deque->front] = ele;
    deque->numOfElements++;
}


ElementType popLeft(Deque* deque){
    assert(deque);

    ElementType temp;
    if(deque->numOfElements > 0){
        temp = deque->a[deque->front];
        if(deque->front == deque->rear){
            deque->front = -1;
            deque->rear = -1;
        }else{
            deque->front = (deque->front + 1) % deque->capacity;
        }
        deque->numOfElements--;
    }

    /* Resize if the size of the array is one quarter of its capacity */
    if(deque->numOfElements < 0.25*deque->capacity) resizeDown(deque);

    return temp;
}

ElementType popRight(Deque* deque){
    assert(deque);
    
    ElementType temp;
    if(deque->numOfElements > 0){
        temp = deque->a[deque->rear];
        if(deque->front == deque->rear){
            deque->front = -1;
            deque->rear = -1;
        }else{
            if(deque->rear - 1 < 0){
                deque->rear = deque->capacity + (deque->rear - 1);
            }else{
                deque->rear = (deque->rear - 1) % deque->capacity;
            }
        }
        deque->numOfElements--;
    }

    /* Resize if the size of the array is one quarter of its capacity */
    if(deque->numOfElements < 0.25*deque->capacity) resizeDown(deque);

    return temp;
}


int DequeSize(Deque* deque){
    assert(deque);
    return deque->numOfElements;
}

int DequeEmpty(Deque* deque){
    assert(deque);
    return deque->numOfElements == 0? 1 : 0;
}