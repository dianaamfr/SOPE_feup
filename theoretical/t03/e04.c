//======================================================================
// e04.c / JAS
// exec()
//----------------------------------------------------------------------
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
int pid;
int status;
char *arg[]={"ls","-laR",NULL};
printf("before fork\n");
pid=fork();
if (pid > 0) {
wait(&status);
printf("I'm the parent (PID=%d)\n\n",getpid()); }
else {
printf("I'm the son (PID=%d)\n\n",getpid());
execvp("ls",arg);
printf("EXEC failed\n");
}
printf ("PID=%d exiting ...\n",getpid());
return 0;
}