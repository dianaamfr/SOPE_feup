#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX 50

int main(void) {
   pid_t pid;
   char hello[]="Hello ";
   char world[]="world!\n";
   int status; 

   pid=fork();

   switch (pid){
      case -1: //erro
         perror("fork");
         break;
      case 0: //filho
            write(STDOUT_FILENO,hello,strlen(hello));
            exit( getpid() % 10);
      break;
      default: //pai
         wait(&status);
         write(STDOUT_FILENO,world,strlen(world));
         
      }


   return 0;
} 