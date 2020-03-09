#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

/*
(*)

//before for loop
Process = 8037
Parent = 3190

//for loop and forks
i==1
1st fork() => 2 processes => parent=8037 and c1=8038 => parent(c1) = 8037, c1 is the 1st child of 8037

i==2
2 forks, one on process parent and other on c1  => 4 processes
->fork() in parent => parent=8037 and c2 = 8043 (2nd child of 8037(parent))
->fork() in c1 => c3 = 8039 (1st child of 8038 (c1))

i==3
4 forks, one on each of the processes (parent,c1,c2,c3) => 8 processes
->fork() in parent => parent=8037 and c4 = 8049 (3rd child of 8037(parent))
->fork() in c1 => c5 = 8044 (2nd child of 8038(c1))
->fork() in c2 => c6 = 8040 (1st child of 8043(c2))
->fork() in c3 => c7 = 8044 (1st child of 8039(c3))
*/

int main(void){
   pid_t pid/*,childPid*/;
   int i, j;
   //int status;

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
         //exit(0); // a eliminar na alinea c) //the loop is executed for each child process (see *)
      }
      else{// simulando o trabalho do pai
         for (j=1; j<=10; j++) {
            sleep(1);
            /*childPid = waitpid(-1,&status,WNOHANG);
            if (childPid < 0) //A value of -1 is returned in case of error
            {
               perror ("waitpid");
               break;
            }
            else if (childPid == 0) break;//If there are child processes but none of them is waiting to be noticed, waitpid will block until one is. 
            //However, if the WNOHANG option was specified, waitpid will return zero instead of blocking.
            else printf("Waited for %d.\n",childPid); //The return value is normally the process ID of the child process whose status is reported*/
            printf("father working ...\n");
         }
      }
   }
   exit(0);
} 