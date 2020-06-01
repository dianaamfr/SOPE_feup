//======================================================================
// f05.c / JAS
// zombie's
// In another terminal, execute command 'ps u'
//----------------------------------------------------------------------
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(void)
{
   int pid;
   pid=fork();
   if (pid > 0) {
      printf("I'm the parent (PID=%d)\n\n",getpid());
      sleep(10); }
   else {
      printf("I'm the son (PID=%d)\n\n",getpid());
   }
   printf ("PID=%d exiting ...\n",getpid());
   return 0;
}