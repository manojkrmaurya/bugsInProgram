// To compile and generate binary: gcc bug7_21285.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

int cacheSize;
int maxCacheSize;
int removeDefaultSize;

char cacheBuffer[100];



void caching(char *cacheData, int cacheDataLen){

  int counter1, counter2;

  if(cacheSize == 0){

      if(cacheDataLen < maxCacheSize){

          memcpy(cacheBuffer,cacheData,cacheDataLen);
          cacheSize = cacheDataLen;

      }else{

          memcpy(cacheBuffer,cacheData,maxCacheSize);
          cacheSize = maxCacheSize;

      }

  }
  else if(cacheSize >= maxCacheSize){

       cacheSize = cacheSize - removeDefaultSize;

       if(cacheSize + cacheDataLen <= maxCacheSize){

           for(counter1 = cacheSize-1,counter2 = 0;counter1 < (cacheSize + cacheDataLen); counter1++, counter2++)
               cacheBuffer[counter1] = cacheData[counter2];

           cacheSize = cacheSize + cacheDataLen;


       }else{

         // when new data size is more than the limit
           for(counter1 = cacheSize-1,counter2 = 0;counter1 < maxCacheSize; counter1++, counter2++)
               cacheBuffer[counter1] = cacheData[counter2];

           cacheSize = maxCacheSize;
       }

  }else{

      // when cacheSize < maxCacheSize

      if(cacheSize + cacheDataLen <= maxCacheSize){

          for(counter1 = cacheSize-1,counter2 = 0;counter1 < (cacheSize + cacheDataLen); counter1++, counter2++)
              cacheBuffer[counter1] = cacheData[counter2];

          cacheSize = cacheSize + cacheDataLen;


      }else{

        // when new data size is more than the limit
          for(counter1 = cacheSize-1,counter2 = 0;counter1 < maxCacheSize; counter1++, counter2++)
              cacheBuffer[counter1] = cacheData[counter2];

          cacheSize = maxCacheSize;
      }

  }

}

void setCache1(){

    caching("abcdefghijklmonpqrstuvwxyabcdefghijklmonpqrstuvwxyabcdefghijklmonpqrstuvwxyabcdefghijklmonpqrstuvwxy",100);
}

void setCache2(){

    caching("abcdefghijklmonpqrstuvwxy",25);
}

void setCache3(){

    caching("abcdefghijklmonpqrstuvwxyabcdefghijklmonpqrstuvwxy",50);
}

void setCache4(){

    caching("abcdefghijklmonpqrstuvwxyabcdefghijklmonpqrstuvwxyabcdefghijklmonpqrstuvwxy",75);
}

void *thread1(void *args) {

    setCache1();
    return 0;
}
void *thread2(void *args) {

    setCache2();
    return 0;
}

void *thread3(void *args) {

    setCache3();
    return 0;
}

void *thread4(void *args) {

    setCache4();
    return 0;
}


int main() {

    maxCacheSize = 100;
    cacheSize = 0;
    removeDefaultSize = 50;
    memset(cacheBuffer,0,maxCacheSize);

    pthread_t objThreads1;
    pthread_t objThreads2;
    pthread_t objThreads3;
    pthread_t objThreads4;

    pthread_create(&objThreads1, 0, thread1, 0);
    pthread_create(&objThreads2, 0, thread2, 0);
    pthread_create(&objThreads3, 0, thread3, 0);
    pthread_create(&objThreads4, 0, thread4, 0);

    return 0;

}
