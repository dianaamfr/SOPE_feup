#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_CMD_SIZE 20
#define MAX_CMD_ARGS 10

int main(void){
   int pid, status;
   int fd;
   char cmd[MAX_CMD_SIZE];
   char c;
   int i,j;

   do{
      printf("minish > ");
      i=0;
      j=0;
      char * args[MAX_CMD_ARGS];
      memset(cmd, 0, MAX_CMD_SIZE);
      for (int k = 0; k<MAX_CMD_ARGS; k++) 
         args[k] = (char *)malloc( MAX_CMD_SIZE  * sizeof(char)); 
      
      while((c = getchar()) != '\n'){
         if(c == ' '){
            cmd[j] = '\0';
            memcpy(args[i],cmd,MAX_CMD_SIZE);
            //args[i] = cmd; 
            memset(cmd, 0, MAX_CMD_SIZE);
            i++;
            j=0;
         }
         else{
            cmd[j] = c;
            j++;
         }
      }
      cmd[j] = '\0';
      memcpy(args[i],cmd,MAX_CMD_SIZE);
      i++;
      args[i] = '\0';

      pid = fork();

      if(pid > 0){ /*parent*/
         wait(&status);
      }
      else{ /*child*/

         if(i >= 3){
            if(strcmp(args[i-2],"-o") == 0){
               fd = open(args[i-1],O_WRONLY|O_CREAT|O_EXCL,0644);
               if(fd == -1){
                  perror(args[i-1]); //throw error with info about the name of the file
                  return 3; //no such process error
               }
               dup2(fd,STDOUT_FILENO);
               args[i-2] = '\0';
            }
         }
         execvp(args[0], args);
         if(strcmp(args[0],"quit") != 0)
            printf("Command not found!\n");
         exit(1);
      }
   } while(strcmp(cmd,"quit") != 0);
}
