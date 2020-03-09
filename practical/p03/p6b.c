#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
   pid_t pid,childPid;
   int i, j;
   int status;

   printf("I'm process %d. My parent is %d.\n", getpid(),getppid());

   for (i=1; i<=3; i++) {
      pid = fork();
      if ( pid < 0) {
         printf("fork error");
         exit(1);
      }
      else if (pid == 0) {
         printf("I'm process %d. My parent is %d. I'm going to work for 1 second ...\n",getpid(),getppid());
         sleep(1); // simulando o trabalho do filho
         printf("I'm process %d. My parent is %d. I finished my work\n", getpid(),getppid());
         exit(0); // a eliminar na alinea c) 
      }
      else{// simulando o trabalho do pai
         for (j=1; j<=10; j++) {
            sleep(1);
            childPid = waitpid(-1,&status,WNOHANG);
            if (childPid < 0) //A value of -1 is returned in case of error
            {
               perror ("waitpid");
               break;
            }
            else if (childPid == 0) break;//If there are child processes but none of them is waiting to be noticed, waitpid will block until one is. 
            //However, if the WNOHANG option was specified, waitpid will return zero instead of blocking.
            else printf("Waited for %d.\n",childPid); //The return value is normally the process ID of the child process whose status is reported
            printf("father working ...\n");
         }
      }
   }
   exit(0);
} 