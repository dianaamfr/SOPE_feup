//======================================================================
// e01.c / JAS
// execl() & execlp()
//----------------------------------------------------------------------
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
int pid;
pid=fork();
if (pid > 0) {
wait(NULL); //father does not care w/exit status of the son ...
printf("I'm the parent (PID=%d)\n\n",getpid()); }
else {
printf("I'm the son (PID=%d)\n\n",getpid());
execl("./e01_aux","e01_aux","3",NULL);
printf(".... \n"); //which message makes sense, here ?
}
printf ("PID=%d exiting ...\n",getpid());
return 0;
}