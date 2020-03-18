#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

void childhandler(int signo) {
   int status;
   pid_t pid;
   
   while((pid = waitpid(0, &status, WNOHANG)) > 0) //No zombies (no lost SIGCHLD)
      printf("Child with PID=%d terminated with exit code %d\n",pid,WEXITSTATUS(status));

   if(WEXITSTATUS(status) != 0) kill(0,SIGTERM);
}

int main(int argc, char* argv[]){
   pid_t pid;
   struct sigaction action;

   if(argc < 2){
      printf("Usage: %s <prog1> <prog2> <prog3> ...",argv[0]);
      exit(1);
   }

   action.sa_handler = childhandler;
   sigemptyset(&action.sa_mask);
   action.sa_flags = 0;

   if (sigaction(SIGCHLD,&action,NULL) < 0)
   {
      fprintf(stderr,"Unable to install SIGCHLD handler\n");
      exit(1);
   }

   for(int i = 1; i < argc;i++){
        pid = fork();

        switch(pid){
            case -1:
               perror("Fork error");
               break;
            case 0://child
               if(execl(argv[i],argv[i],NULL) == -1){
                  perror(argv[i]);
                  exit(1);
               }
               break;
            default://parent
               pause();
         }
   }
  
   exit(0);
}