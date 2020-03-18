#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
   if(argc < 2){
      printf("Usage: %s <message>...",argv[0]);
      exit(1);
   }

   int t = 30;

   while(t > 0){
      printf("%s\n",argv[1]);
      sleep(5);
      t-=5;
   }

   printf("Exiting prog...\n");
   exit(0);
}