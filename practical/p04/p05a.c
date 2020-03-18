// PROGRAMA p04a.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

int main(void)
{
   struct sigaction action;
   pid_t pid;
   int i, n, status;

   // prepare the 'sigaction struct'
   action.sa_handler =  SIG_IGN;
   sigemptyset(&action.sa_mask);
   action.sa_flags = 0;
   // install the handler
   sigaction(SIGCHLD,&action,NULL);

   for (i=1; i<=3; i++) {
      pid=fork(); 
   
      if (pid == 0){
         printf("CHILD no. %d (PID=%d) working ... \n",i,getpid());
         sleep(i*7); // child working ...
         printf("CHILD no. %d (PID=%d) exiting ... \n",i,getpid());
         exit(0);
      }
   }

   for (i=1 ;i <= 4; i++) {
      printf("PARENT: working hard (task no. %d) ...\n",i);

      n=20; while((n=sleep(n))!=0);

      printf("PARENT: end of task no. %d\n",i);
      printf("PARENT: waiting for child no. %d ...\n",i);

      if (pid != -1)
         printf("PARENT: child with PID=%d terminated with exit code %d\n",pid,WEXITSTATUS(status));

   }
   exit(0);
} 