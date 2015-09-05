// To compile and generate binary: gcc bug8_21287.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

int decrement_refcount;

void setValue(){

  decrement_refcount--;
}


void *thread1(void *args) {

    setValue();
    return 0;
}
void *thread2(void *args) {

    setValue();
    return 0;
}

void *thread3(void *args) {

    setValue();
    return 0;
}

int main() {


    pthread_t objThreads1;
    pthread_t objThreads2;
    pthread_t objThreads3;

    pthread_create(&objThreads1, 0, thread1, 0);
    pthread_create(&objThreads2, 0, thread2, 0);
    pthread_create(&objThreads3, 0, thread3, 0);

    return 0;

}
