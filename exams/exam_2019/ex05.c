

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

   if(argc != 2){
      fprintf(stderr,"Args error");
      exit(1);
   }

   size_t bufsize = MAXLINE + 1;
   char * exp = malloc(bufsize), * res = malloc(bufsize);
   int fileFd, pipeFd1[2], pipeFd2[2];
   pid_t pid;

   pipe(pipeFd1);
   pipe(pipeFd2);

   pid = fork();

   if(pid == 0){ // CHILD
      close(pipeFd1[WRITE]);
      close(pipeFd2[READ]);

      dup2(pipeFd1[READ],STDIN_FILENO);
      dup2(pipeFd2[WRITE],STDOUT_FILENO);

      execlp("bc", "bc", "-qi", NULL);   
   }

   close(pipeFd1[READ]);
   close(pipeFd2[WRITE]);

   if( (fileFd = open(argv[1],O_CREAT|O_WRONLY|O_APPEND,0644)) == -1){
      fprintf(stderr, "Open file error");
      exit(1);
   }

   do{
      printf("Input an arithmetic expression (END = Ctrl-D): ");
      if(getline(&exp, &bufsize, stdin) < 0) break;

      write(pipeFd1[WRITE], exp, strlen(exp));

      int n1 = read(pipeFd2[READ],exp, strlen(exp));
      exp[strlen(exp)-1] = '\0';

      int n2 = read(pipeFd2[READ],res, MAXLINE);
      res[strlen(exp)-1] = '\0';

      char finalExp[n1 + n2 + 4];
      sprintf(finalExp, "%s = %s\n", exp, res);
   
      write(fileFd, finalExp, strlen(finalExp));
      
   } while(1);

   free(res);
   free(exp);

   return 0;
}