// Buggy code in which it should give segmentation fault or double free
// compilation: gcc bug9_3295.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

struct worker{

    int busy;
    char *proc_info;


};

int printf_thd(struct worker *objWorker){


    objWorker->busy++;

    if(objWorker->proc_info != NULL){


        // do some action

        free(objWorker->proc_info);

        objWorker->proc_info = (char *)malloc(sizeof(char)*100);
        if(objWorker->proc_info == NULL)
                return(-1);
        else{

            memset(objWorker->proc_info,0,100);
            memcpy(objWorker,"testing",7);        }

    }
}

void *thread1(void *args) {

    struct worker *tempObjWorker = (struct worker *)args;
    printf_thd(tempObjWorker);
    return 0;
}


int main() {

    struct worker *objWorker = (struct worker *)malloc(sizeof(struct worker *));
    if(objWorker == NULL){

        printf("\nExit");
        return(-1);

    }else{

        objWorker->proc_info = (char *)malloc(sizeof(char)*100);
        memset(objWorker->proc_info,0,100);
        memcpy(objWorker,"testing",7);
    }

    objWorker->busy = 0;

    pthread_t objThreads1;
    pthread_t objThreads2;
    pthread_t objThreads3;
    pthread_t objThreads4;

    pthread_create(&objThreads1, 0, thread1, objWorker);
    pthread_create(&objThreads2, 0, thread1, objWorker);
    pthread_create(&objThreads3, 0, thread1, objWorker);
    pthread_create(&objThreads4, 0, thread1, objWorker);

    //if(objWorker->proc_info != NULL)free(objWorker->proc_info);
    //if(objWorker != NULL)free(objWorker);

    return 0;

}
