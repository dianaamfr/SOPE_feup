#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int v = 0;

void sigusr_handler(int);

int main(){
   
   // prepare the 'sigaction struct'
   struct sigaction action;
   action.sa_handler = sigusr_handler;
   sigemptyset(&action.sa_mask); //all signals are delivered
   action.sa_flags = 0;

   // install the handler 
   if (sigaction(SIGUSR1,&action,NULL) < 0)
   {
      fprintf(stderr,"Unable to install SIGUSR handler\n");
      exit(1);
   }
   // install the handler 
   if (sigaction(SIGUSR2,&action,NULL) < 0)
   {
      fprintf(stderr,"Unable to install SIGUSR handler\n");
      exit(1);
   }

   for (;;);
   exit(0);

}

void sigusr_handler(int signo){
   if(signo == SIGUSR1){
      v++;
      printf("v++ => v = %d\n",v);
   }
   if(signo == SIGUSR2){
      v--;
      printf("v++ => v = %d\n",v);
   }
}