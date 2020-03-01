#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/*Altere o programa por forma a apresentar uma mensagem de utilização "usage: nome_do_executável
file1 file2" caso não sejam passados os nomes de dois ficheiros como argumentos da linha de comando,
terminando imediatamente após apresentar aquela mensagem*/

static void exithand1(void) {
   printf("Executing exit handler 1!\n");
   exit(1);
}

static void exithand2(void) {
   printf("Executing exit handler 2!\n");
   exit(2);
}

int main(int argc, char* argv[])
{
   FILE *src1, *src2;
   char *file1 = argv[1];
   char *file2 = argv[2];

   if(argc != 3){
      printf("usage: nome_do_executável file1 file2\n");
      exit(0);
   }

   if((src1= fopen(file1,"r")) ==  NULL){
     atexit(exithand1);
   }
   else fclose(src1);

   if((src2 = fopen(file2,"r")) == NULL){
      atexit(exithand2);
   }
   else fclose(src2);

   
   printf("Main done!\n");
   
   exit(0); // zero é geralmente indicativo de "sucesso"
}