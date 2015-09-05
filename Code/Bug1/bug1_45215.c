#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

struct worker{

    int busy;

};

int proxy_balancer_pre_request(struct worker *objWorker){

    while(1){

        objWorker->busy++;
        sleep(5);

        printf("\nBusy value %d",objWorker->busy);
        if(objWorker->busy >= 1000)
            break;
    }

}

void *thread1(void *args) {

    struct worker *tempObjWorker = (struct worker *)args;
    proxy_balancer_pre_request(tempObjWorker);
    return 0;
}

void *thread2(void *args) {

    struct worker *tempObjWorker = (struct worker *)args;
    proxy_balancer_pre_request(tempObjWorker);
    return 0;
}

int main() {

    struct worker *objWorker = (struct worker *)malloc(sizeof(struct worker *));
    if(objWorker == NULL){

        printf("\nExit");
        return(-1);
    }

    objWorker->busy = 0;

    pthread_t objThreads1;
    pthread_t objThreads2;

    pthread_create(&objThreads1, 0, thread1, objWorker);
    pthread_create(&objThreads2, 0, thread2, objWorker);

    return 0;

}
