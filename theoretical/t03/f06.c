//======================================================================
// f06.c / JAS
// Tree of child processes with some zombies
// In another terminal, execute command 'ps u'
//----------------------------------------------------------------------
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(void)
{
   int i, pid;
   for (i=1;i<=3;i++) {
      pid=fork();
      if (pid > 0) {
         printf("I'm the parent (PID=%d)\n\n",getpid());
         sleep(5);
      }
      else {
         printf("I'm the son (PID=%d). My parent is %d\n\n",getpid(),getppid());
         break; // NOTE THIS
      }
   }
   printf ("PID=%d exiting ...\n",getpid());
   return 0;
}