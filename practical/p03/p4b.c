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

   pid=fork();

   switch (pid){
      case -1: //erro
         perror("fork");
         break;
      case 0: //filho
            waitpid(getppid(), 0, 0);
            write(STDOUT_FILENO,world,strlen(world));
      break;
      default: //(>1) pai
         write(STDOUT_FILENO,hello,strlen(hello));
      }
   return 0;
} 