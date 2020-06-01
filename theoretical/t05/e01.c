#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define MAXLINE 12
#define READ 0
#define WRITE 1

int main(void){
   int n, fd[2];
   pid_t pid;
   char line[MAXLINE];

   if(pipe(fd) < 0){
      fprintf(stderr, "Pipe Error");
      exit(1);
   }

   if((pid = fork()) < 0){
      fprintf(stderr, "Fork Error");
      exit(2);
   }

   else if(pid > 0){ // Pai
      close(fd[READ]);
      write(fd[WRITE], "Hello World",12);
   }

   else{ // Filho
      close(fd[WRITE]);
      n = read(fd[READ], line, MAXLINE);
      write(STDOUT_FILENO,line, n);

   }
}