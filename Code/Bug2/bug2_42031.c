#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

pthread_mutex_t lock;

void heavyLoaded(){

    if(pthread_mutex_trylock(&lock)==0){

        printf("\nHeavy Loaded Thread");
        sleep(60);
        pthread_mutex_unlock(&lock);

    }else
        printf("\nHeavy loaded thread start request fails.");
}

void lessLoaded(){

    if(pthread_mutex_trylock(&lock)==0){

        printf("\nLess Loaded Thread");
        sleep(5);

        pthread_mutex_unlock(&lock);
    }else
        printf("\nLess loaded thread start request fails.");
}

void *thread1(void *args) {

    while(1){

        heavyLoaded();
    }
    return 0;
}
void *thread2(void *args) {

    while(1){

        heavyLoaded();
    }
    return 0;
}
void *thread3(void *args) {

    while(1){

        heavyLoaded();
    }
    return 0;
}
void *thread4(void *args) {

    while(1){

        heavyLoaded();
    }
    return 0;
}
void *thread5(void *args) {

    while(1){

        heavyLoaded();
    }
    return 0;

}
void *thread6(void *args) {

    while(1){

        heavyLoaded();
    }
    return 0;
}
void *thread7(void *args) {

    while(1){

        heavyLoaded();
    }
    return 0;
}
void *thread8(void *args) {

    while(1){

        heavyLoaded();
    }
    return 0;
}
void *thread9(void *args) {

    while(1){

        lessLoaded();
    }
    return 0;
}
void *thread10(void *args) {

    while(1){

        lessLoaded();
    }
    return 0;
}


int main() {

    pthread_mutex_init(&lock, NULL);

    pthread_t objThreads1;
    pthread_t objThreads2;
    pthread_t objThreads3;
    pthread_t objThreads4;
    pthread_t objThreads5;
    pthread_t objThreads6;
    pthread_t objThreads7;
    pthread_t objThreads8;
    pthread_t objThreads9;
    pthread_t objThreads10;

    pthread_create(&objThreads1, 0, thread1, 0);
    pthread_create(&objThreads2, 0, thread2, 0);
    pthread_create(&objThreads3, 0, thread3, 0);
    pthread_create(&objThreads4, 0, thread4, 0);
    pthread_create(&objThreads5, 0, thread5, 0);
    pthread_create(&objThreads6, 0, thread6, 0);
    pthread_create(&objThreads7, 0, thread7, 0);
    pthread_create(&objThreads8, 0, thread8, 0);
    pthread_create(&objThreads9, 0, thread9, 0);
    pthread_create(&objThreads10, 0, thread10, 0);


    return 0;

}
