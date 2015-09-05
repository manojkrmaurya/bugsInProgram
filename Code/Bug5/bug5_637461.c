#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t mWriteThread;

void waitOnWriteThread(){

    if(mWriteThread == getpid()){

        // Perform some task

        mWriteThread = 0;
    }
}

void writeToDisk(){

    waitOnWriteThread();

    // Other operations
}



void *thread1(void *args) {

    mWriteThread = getpid();
    writeToDisk();
    return 0;
}
void *thread2(void *args) {

    mWriteThread = getpid();
    writeToDisk();
    return 0;
}


int main() {


    pthread_t objThreads1;
    pthread_t objThreads2;

    pthread_create(&objThreads1, 0, thread1, 0);
    pthread_create(&objThreads2, 0, thread2, 0);

    return 0;

}
