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
   int fd, fd_pipe1[2],fd_pipe2[2], n;
   char expression[MAXLINE], result[MAXLINE], final[MAXLINE*2 + 3];

   if(argc != 2){
      fprintf(stderr,"Usage: %s <destination>",argv[0]);
      exit(1);
   }

   pipe(fd_pipe1);
   pipe(fd_pipe2);

   pid_t pid = fork();

   if(pid > 0){ // Parent
      close(fd_pipe1[READ]);
      close(fd_pipe2[WRITE]);
      
      if((fd = open(argv[1], O_CREAT|O_WRONLY|O_APPEND,0644)) == -1){
         fprintf(stderr,"Error opening file in write only mode");
         exit(1);
      }
       
      do{
         printf("Input expression (END = CTRL-D): ");

         if(fgets(expression, MAXLINE, stdin) == NULL) break;

         n = strlen(expression);
         write(fd_pipe1[WRITE], expression, n);

         read(fd_pipe2[READ],expression,MAXLINE);
         expression[strlen(expression)-1] = '\0';
         read(fd_pipe2[READ],result,MAXLINE);

         sprintf(final,"%s = %s",expression,result);

         write(fd,final,strlen(final));

         memset(expression,'\0',MAXLINE);
         memset(result,'\0',MAXLINE);
         memset(final,'\0',MAXLINE);

      } while(1);

      close(fd_pipe1[WRITE]);
      close(fd_pipe2[READ]);
      close(fd);
   }
   else if(pid == 0){ // Child
      close(fd_pipe1[WRITE]);
      close(fd_pipe2[READ]);
      
      dup2(fd_pipe2[WRITE],STDOUT_FILENO);
      dup2(fd_pipe1[READ],STDIN_FILENO);
      execlp("bc", "bc", "-qi", NULL);
   }
   else{
     fprintf(stderr,"Fork error");
     exit(1); 
   }
      
   return 0;
}