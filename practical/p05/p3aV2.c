#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#define READ 0
#define WRITE 1

#define MAXLINE 1000

int main(int argc, char *argv[])
{
   char line[MAXLINE];
   FILE *f;
   int fd[2];
   pid_t pid;
   int n;

   if (argc != 2) { 
      printf("usage: %s filename\n",argv[0]);
      exit(1); 
   }

   pipe(fd);

   pid = fork();

   if(pid > 0){
      close(fd[READ]);

      //open file in read mode
      if ((f = fopen(argv[1], "r")) == NULL){
         fprintf(stderr,"Couldn't open %s\n", argv[1]);
         exit(1);
      }
      
      //read lines from names file while it has something to read
      while (fgets(line, MAXLINE, f) != NULL){ 
         n=strlen(line); 
         if (write(fd[WRITE],line,n) != n)
            fprintf(stderr,"Error writing to pipe\n"); 
      }

      //tests the error indicator for the stream  pointed to  by stream, returning nonzero if it is set
      if (ferror(f)){
         fprintf(stderr,"fgets error");
         exit(1);
      }
   }
   else if(pid == 0){ //child
    
      close(fd[WRITE]);

      //child read from pipe instead of stdin
      dup2(fd[READ],STDIN_FILENO); 

      //sorter prints to stdout by default
      execlp("sort", "sort", NULL);
      perror("Error calling exec!\n");
		exit(1);
   }

   exit(0);
} 