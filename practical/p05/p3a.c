#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#define READ 0
#define WRITE 1

#define MAXLINE 1000
#define SORTER "sort"

int main(int argc, char *argv[])
{
   char line[MAXLINE];
   FILE *fpin, *fpout;

   if (argc != 2) { 
      printf("usage: %s filename\n",argv[0]);
      exit(1); 
   }

   //open file in read mode
   if ((fpin = fopen(argv[1], "r")) == NULL){
      fprintf(stderr,"Couldn't open %s\n", argv[1]);
      exit(1);
   }

   //opens sorter in write-only mode by creating a pipe, forking, and invoking the shell
   //Retorna um apontador para um ficheiro (FILE *) que será o ficheiro de entrada ou de saída do programa ('w')
   if ((fpout = popen(SORTER, "w")) == NULL){
      fprintf(stderr,"Popen error\n");
      exit(1);
   }  
   
   //read lines from names file while it has something to read
   while (fgets(line, MAXLINE, fpin) != NULL){ 

      // fputs writes  the  string  s to sorter, without its terminating null byte ('\0')
      if (fputs(line, fpout) == EOF){
         printf("Fputs error to pipe"); 
         exit(1);
      }
   }

   //tests the error indicator for the stream  pointed to  by stream, returning nonzero if it is set
   if (ferror(fpin)){
      fprintf(stderr,"fgets error");
      exit(1);
   }

   //close sorter 
   if (pclose(fpout) == -1){
      fprintf(stderr,"pclose error");
      exit(1);
   }

   exit(0);
} 