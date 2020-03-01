
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define MAX_CHARS_TO_READ 700

int main(int argc, char *argv[]){
   FILE *source, *dest;
   char buffer[MAX_CHARS_TO_READ+1];
   
   if(argc != 3){
      printf("\nUsage: %s <source> <destination>\n",argv[0]);
      return 1;
   }

   if((source = fopen(argv[1],"r")) == NULL){
      printf("Error %d reading file %s!\n ", errno,argv[1]);
      exit(EXIT_FAILURE); 
   }

   if((dest = fopen(argv[2],"w")) == NULL){
      printf("Error %d reading file %s!\n ", errno,argv[2]);
      exit(EXIT_FAILURE); 
   }

   fread(buffer,MAX_CHARS_TO_READ+1,1,source);
   fwrite(buffer,1,strlen(buffer),dest);

   fclose(source);
   fclose(dest);
   
   return 0;
}