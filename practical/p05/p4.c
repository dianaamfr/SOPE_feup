#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{
   int fd[2];
   pid_t pid;

   if (argc != 3) { 
      printf("usage: %s <dir> <arg>\n",argv[0]);
      exit(1); 
   }

   pipe(fd);

   pid = fork();

   if(pid > 0){
      close(fd[READ]);
      
      //em vez de escrever na consola escreve no pipe
      dup2(fd[WRITE], STDOUT_FILENO);
   
      execlp("ls", "ls", argv[1], "-laR", NULL);
      perror("Error calling exec!\n");
		exit(1);   
   }
   else if(pid == 0){ //child
      int fd1[2];
      pipe(fd1);

      close(fd[WRITE]);
      //child reads from pipe instead of stdin
      dup2(fd[READ],STDIN_FILENO); 

      pid = fork();

      if(pid > 0){
         close(fd1[READ]);
         
         //em vez de escrever na consola escreve no 2º pipe
         dup2(fd1[WRITE], STDOUT_FILENO);
         execlp("grep", "grep", argv[2], NULL);
         perror("Error calling exec!\n");
         exit(1); 
      }
      else if(pid == 0){
         close(fd1[WRITE]);

         //child reads from pipe instead of stdin
         dup2(fd1[READ],STDIN_FILENO); 
         
         execlp("sort", "sort", NULL);
         perror("Error calling exec!\n");
		   exit(1); 
      }
      else{ //error
         fprintf(stderr,"Fork error!\n");
         exit(1);
      }   
      
   }
   else{ //error
      fprintf(stderr,"Fork error!\n");
      exit(1);
   }

   exit(0);
} 