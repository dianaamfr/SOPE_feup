#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>  
#include <sys/stat.h>

#define MAXLINE 1000
#define READ 0
#define WRITE 1

int main(int argc, char * argv[]){
   int fd, fd_pipe[2], n;
   char expression[MAXLINE];

   if(argc != 2){
      fprintf(stderr,"Usage: %s <destination>",argv[0]);
      exit(1);
   }

   pipe(fd_pipe);

   pid_t pid = fork();

   if(pid > 0){ // Parent
      close(fd_pipe[READ]);
      do{
         printf("Input expression (END = CTRL-D): ");

         if(fgets(expression, MAXLINE, stdin) == NULL) break;

         n = strlen(expression);
         write(fd_pipe[WRITE], expression, n);
         
         memset(expression,'\0',MAXLINE);

      } while(1);

      close(fd_pipe[WRITE]);
   }
   else if(pid == 0){ // Child
      close(fd_pipe[WRITE]);

      if((fd = open(argv[1], O_CREAT|O_WRONLY|O_APPEND,0644)) == -1){
         fprintf(stderr,"Error opening file in write only mode");
         exit(1);
      } 
      
      dup2(fd,STDOUT_FILENO);
      dup2(fd_pipe[READ],STDIN_FILENO);
      execlp("bc", "bc", "-qi", NULL);
   }
   else{
     fprintf(stderr,"Fork error");
     exit(1); 
   }
      
   return 0;
}