// PROGRAMA p04a.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void childhandler(int signo) {
   int status;
   pid_t pid;
   
   while((pid = waitpid(0, &status, WNOHANG)) > 0) //No zombies (no lost SIGCHLD)
      printf("Child with PID=%d terminated with exit code %d\n",pid,WEXITSTATUS(status));
}

int main(void)
{
   struct sigaction action;
   pid_t pid;
   int i, n;

   // prepare the 'sigaction struct'
   action.sa_handler = childhandler;
   sigemptyset(&action.sa_mask);
   action.sa_flags = 0;
   // install the handler
   sigaction(SIGCHLD,&action,NULL);

   for (i=1; i<=9; i++) {
      pid=fork(); 
   
      if (pid == 0){
         printf("CHILD no. %d (PID=%d) working ... \n",i,getpid());
         sleep(15); // child working ...
         printf("CHILD no. %d (PID=%d) exiting ... \n",i,getpid());
         exit(0);
      }
   }

   for (i=1 ;i <= 10; i++) {
      printf("PARENT: working hard (task no. %d) ...\n",i);

      n=20; while((n=sleep(n))!=0);

      printf("PARENT: end of task no. %d\n",i);
      printf("PARENT: waiting for child no. %d ...\n",i);

   }
   exit(0);
} 