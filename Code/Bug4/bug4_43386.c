#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>


void readWriteFile(){

    char tempData[100];
    int nRead;

    FILE *fpr;
    FILE *fpw;

    fpr = fopen("readFile.txt","rb");
    fpw = fopen("writeFile.txt", "wb");

    if(fpr == NULL || fpw == NULL)return;

    do
    {
              memset(tempData,0,100);
              nRead = fread(tempData,1,100,fpr);

              if(nRead > 0)
              {
                      fwrite(tempData,1,nRead,fpw);
                      if(ferror(fpw)||ferror(fpr))
                       {

                          fclose(fpw);
                          fclose(fpr);
                          return;
                       }
              }

     }while(nRead!=0 || !feof(fpr));

     fclose(fpw);
     fclose(fpr);

}

void replaceFile(){

    system("mv replaceFile.txt readFile.txt");
}


void *thread1(void *args) {

    readWriteFile();
    return 0;
}
void *thread2(void *args) {

    replaceFile();
    return 0;
}


int main() {


    pthread_t objThreads1;
    pthread_t objThreads2;

    pthread_create(&objThreads1, 0, thread1, 0);
    pthread_create(&objThreads2, 0, thread2, 0);

    return 0;

}
