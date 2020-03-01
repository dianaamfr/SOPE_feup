#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define BUF_LENGTH 256

int main(int argc, char* argv[])
{
   FILE *src, *dst;
   char buf[BUF_LENGTH];
   char *file1 = argv[1];
   char *file2 = argv[2];

   if((src = fopen(file1,"r")) ==  NULL){
      printf("%d\n",errno);
      exit(1);
   }
   if((dst = fopen(file2,"w")) == NULL){
      printf("%d\n",errno);
      exit(2);
   }
   while((fgets(buf, BUF_LENGTH, src)) != NULL )
   {
      fputs(buf, dst);
   }

   fclose(src);
   fclose(dst);
   
   exit(0); // zero é geralmente indicativo de "sucesso"
}