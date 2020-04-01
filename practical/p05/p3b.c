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
   int fd[2];
   pid_t pid;

   if (argc != 2) { 
      printf("usage: %s filename\n",argv[0]);
      exit(1); 
   }

   pipe(fd);

   pid = fork();

   if(pid > 0){
      close(fd[READ]);
      
      //em vez de escrever na consola escreve no pipe
      dup2(fd[WRITE], STDOUT_FILENO);
      execlp("cat", "cat", argv[1], NULL);

      perror("Error calling exec!\n");
		exit(1);   
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
   else{ //error
      fprintf(stderr,"Fork error!\n");
      exit(1);
   }

   close(fd[WRITE]);
   exit(0);
} 