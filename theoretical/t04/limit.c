#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

void childhandler(int signo);
int delay;

int main(int argc, char *argv[])
{
   pid_t pid;
   int status;
   pid_t childPid;
   signal(SIGCHLD, childhandler);

   pid = fork();
   
   if (pid == 0){/* child */
      execvp(argv[2], &argv[2]);
      printf("exec error\n");
   } 
   else /* parent */
   {
      sscanf(argv[1], "%d", &delay); /* read delay from command line */
      sleep(delay);
      printf("Program %s exceeded limit of %d seconds!\n", argv[2], delay);
      childPid = waitpid(-1,&status,WNOHANG);
      kill(childPid, SIGKILL);
   }

   return 0;
}
void childhandler(int signo) /* Executed if child dies before parent */
{
   int status;
   pid_t pid;
   pid = wait(&status);
   printf("Child %d terminated within %d seconds.\n", pid, delay);
   exit(0);
}