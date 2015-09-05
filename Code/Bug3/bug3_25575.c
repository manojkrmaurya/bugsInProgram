#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

pthread_mutex_t lock;
char *dataPtr;
FILE *fpr;


void resetFilePtr(){

    while(1){

        if(pthread_mutex_trylock(&lock)==0){

            fclose(fpr);
            fpr = NULL;

            pthread_mutex_unlock(&lock);
            break;

        }else
            continue;
    }
}

void resetCharPtr(){

    while(1){


        if(pthread_mutex_trylock(&lock)==0){

            if(dataPtr != NULL)free(dataPtr);

            pthread_mutex_unlock(&lock);
            break;

        }else
            continue;

    }

}

void accessVariables(){

    while(1){


        if(pthread_mutex_trylock(&lock)==0){

            memcpy(dataPtr,"TESTING",7);
            fclose(fpr);

            pthread_mutex_unlock(&lock);
            break;

        }else
            continue;

    }
}

void *thread1(void *args) {

    resetFilePtr();
    return 0;
}
void *thread2(void *args) {

    resetCharPtr();
    return 0;
}
void *thread3(void *args) {

    accessVariables();
    return 0;
}


int main() {


    fpr = fopen("bug3_25575.c","r");
    if(fpr == NULL)
        return(-1);

    dataPtr = (char *)malloc(sizeof(char)*200);
    if(dataPtr == NULL)
        return(-1);

    pthread_mutex_init(&lock, NULL);

    pthread_t objThreads1;
    pthread_t objThreads2;
    pthread_t objThreads3;

    pthread_create(&objThreads1, 0, thread1, 0);
    pthread_create(&objThreads2, 0, thread2, 0);
    pthread_create(&objThreads3, 0, thread3, 0);

    return 0;

}
