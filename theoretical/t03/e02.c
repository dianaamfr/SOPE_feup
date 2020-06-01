//======================================================================
// e02.c / JAS
// exec()
//----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
int pid;
int status;
pid=fork();
if (pid > 0) {
wait(&status);
printf("I'm the parent (PID=%d)\n\n",getpid());
printf("My son exited with EXIT CODE = %d\n",WEXITSTATUS(status));}
else {
printf("I'm the son (PID=%d)\n\n",getpid());
execlp("cat","cat","e02.c",">","e02_copy.c",NULL);
// note the "no such file or directory" errors of "cat"...!
printf("exec() failed !!! \n");
exit(1);
}
printf ("PID=%d exiting ...\n",getpid());
return 0;
}