#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>

int v = 0;
pid_t childPid;

#define n 50

void sigusr_handler(int);

int main(){
   pid_t pid;
   time_t t;
   int status; 

   // prepare the 'sigaction struct'
   struct sigaction action;
   action.sa_handler = sigusr_handler;
   sigemptyset(&action.sa_mask); //all signals are delivered
   action.sa_flags = 0;

   // install the handler for sigusr1 and sigusr2
   if (sigaction(SIGUSR1,&action,NULL) < 0)
   {
      fprintf(stderr,"Unable to install SIGUSR1 handler\n");
      exit(1);
   }
   // install the handler 
   if (sigaction(SIGUSR2,&action,NULL) < 0)
   {
      fprintf(stderr,"Unable to install SIGUSR2 handler\n");
      exit(1);
   }

   pid = fork();

   switch(pid){
   case -1:
      perror("fork error");
      break;
   case 0: //child
      for(int i = 0; i < n; i++){
         pause();
         printf("v = %d\n",v);
      }
   default: //parent
      srand((unsigned) time(&t));
      for(int i = 0; i < n + 1; i++){
         if(rand() % 2 == 0)
            kill(pid,SIGUSR1);
         else
            kill(pid,SIGUSR2);
         sleep(1);
      }

      while(waitpid(pid,&status,0) == -1){
         if(errno != EINTR){  
            break;
         }
         else{
            kill(pid,SIGKILL); 
            break;
         }
      }
      break;
   }
   exit(0);
}

void sigusr_handler(int signo){
   if(signo == SIGUSR1){
      v++;
   }
   if(signo == SIGUSR2){
      v--;
   }
}