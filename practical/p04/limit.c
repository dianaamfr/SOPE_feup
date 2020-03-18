#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int alarmflag = 0;

void alarmhandler(int signo)
{
   printf("Alarm received ...\n");
   alarmflag = 1;
}

int main(int argc, char* argv[]){
   pid_t pid;
   struct sigaction action;
   int delay = 0;

   if(argc < 3){
      printf("Usage: %s <seconds> <prog> <prog_arg1> <prog_arg2> ...",argv[0]);
      exit(1);
   }

   action.sa_handler = alarmhandler;
   sigemptyset(&action.sa_mask);
   action.sa_flags = 0;

   if (sigaction(SIGALRM,&action,NULL) < 0)
   {
      fprintf(stderr,"Unable to install SIGALRM handler\n");
      exit(1);
   }

   pid = fork();

   switch(pid){
      case -1:
         perror("Fork error");
         break;
      case 0://child
         if(execv(argv[2],&argv[2]) == -1){
            perror(argv[2]);
            exit(1);
         }
         break;
      default://parent
         sscanf(argv[1],"%d",&delay);
         alarm(delay);
         if (!alarmflag) pause();
         printf("Program exceeded limit of %d seconds!\n", delay);
         kill(pid,SIGKILL);
   }

   exit(0);
}