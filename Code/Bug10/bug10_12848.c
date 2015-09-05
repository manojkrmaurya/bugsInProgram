// Buggy code in which it should give segmentation fault or double free
// compilation: gcc bug10_12848.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

struct queryCache{

    int queryId;
    char *inputQuery;
    int inputQueryLen;
};

int cache_resizing(struct queryCache *objQuery){

    struct queryCache *tempObjQuery;


    if(objQuery->inputQuery != NULL){


        // Resizing


        tempObjQuery->inputQuery = (char *)malloc(sizeof(char)*(objQuery->inputQueryLen+100));
        if(tempObjQuery->inputQuery == NULL)
                return(-1);
        else{


            memset(tempObjQuery->inputQuery,0,objQuery->inputQueryLen+100);
            memcpy(tempObjQuery->inputQuery,objQuery->inputQuery,objQuery->inputQueryLen+100);
            free(objQuery->inputQuery);
        }

    }
}

void store_query_display(struct queryCache *objQuery){

    if(objQuery->inputQuery != NULL){

        printf("\nQuery : %s",objQuery->inputQuery);
    }

}

void *thread1(void *args) {

    struct queryCache *tempObjQuery = (struct queryCache *)args;
    cache_resizing(tempObjQuery);
    return 0;
}

void *thread2(void *args) {

    struct queryCache *tempObjQuery = (struct queryCache *)args;
    store_query_display(tempObjQuery);
    return 0;
}


int main() {

    struct queryCache *objQuery = (struct queryCache *)malloc(sizeof(struct queryCache *));
    if(objQuery == NULL){

        printf("\nExit");
        return(-1);

    }else{

        objQuery->inputQuery = (char *)malloc(sizeof(char)*100);
        memset(objQuery->inputQuery,0,100);
        memcpy(objQuery->inputQuery,"testing",7);
        objQuery->inputQueryLen = 7;
        objQuery->queryId = 1;
    }


    pthread_t objThreads1;
    pthread_t objThreads2;
    pthread_t objThreads3;
    pthread_t objThreads4;

    pthread_create(&objThreads1, 0, thread1, objQuery);
    pthread_create(&objThreads2, 0, thread2, objQuery);
    pthread_create(&objThreads3, 0, thread1, objQuery);
    pthread_create(&objThreads4, 0, thread2, objQuery);


    return 0;

}
