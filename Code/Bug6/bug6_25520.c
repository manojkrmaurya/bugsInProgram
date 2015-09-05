// To compile and generate binary: gcc bug6_25520.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

int logBufferSize;
char buffer[1000];

void writeToDisk(char *fileName){

    char tempData[100];
    char *tempBufferPtr;
    int continueFlag;
    int remainingRead;

    FILE *fpw;

    fpw = fopen(fileName, "wb");

    if(fpw == NULL)return;

    tempBufferPtr = buffer;
    remainingRead = logBufferSize;

    do
    {
              memset(tempData,0,100);

              if(remainingRead < 100){

                  continueFlag = 0;

                  memcpy(tempData,tempBufferPtr,remainingRead);
                  fwrite(tempData,1,remainingRead,fpw);


              }else{

                  continueFlag = 1;

                  memcpy(tempData,tempBufferPtr,100);
                  fwrite(tempData,1,100,fpw);

                  tempBufferPtr = tempBufferPtr + 100;
                  remainingRead = remainingRead - 100;
              }

     }while(continueFlag != 0);

     fclose(fpw);

}

void setConfig1(){

  logBufferSize = 100;
  strcpy(buffer,"abcdefghijklmnopqresuvwxyabcdefghijklmnopqresuvwxyabcdefghijklmnopqresuvwxyabcdefghijklmnopqresuvwxy");
  writeToDisk("dataWrite1.txt");

}

void setConfig2(){

  logBufferSize = 150;
  strcpy(buffer,"abcdefghijklmnopqresuvwxyabcdefghijklmnopqresuvwxyabcdefghijklmnopqresuvwxyabcdefghijklmnopqresuvwxyabcdefghijklmnopqresuvwxyabcdefghijklmnopqresuvwxy");
  writeToDisk("dataWrite2.txt");

}

void *thread1(void *args) {

    setConfig1();
    return 0;
}
void *thread2(void *args) {

    setConfig2();
    return 0;
}


int main() {


    pthread_t objThreads1;
    pthread_t objThreads2;

    pthread_create(&objThreads1, 0, thread1, 0);
    pthread_create(&objThreads2, 0, thread2, 0);

    return 0;

}
