// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo)
{
 printf("In SIGINT signal handler ...\n");
}
int main(void)
{
 struct sigaction action; 

// prepare the 'sigaction struct' 
 action.sa_handler = sigint_handler;
 sigemptyset(&action.sa_mask); //all signals are delivered
 action.sa_flags = 0;
 
 // install the handler 
 if (sigaction(SIGINT,&action,NULL) < 0)
 {
   fprintf(stderr,"Unable to install SIGINT handler\n");
   exit(1);
 }

 sigset_t mask;
 // ignoring every possible signal
 sigfillset(&mask);//all signals blocked
 sigdelset(&mask,SIGINT); //...except SIGALRM 

 if (sigprocmask(SIG_SETMASK, &mask, NULL) < 0)
 {
   fprintf(stderr,"Unable to install mask\n");
   exit(1);
 }
 printf("Sleeping for 30 seconds ...\n");
 unsigned int timeLeft = 30;
 while(timeLeft > 0){
    timeLeft=sleep(timeLeft);
 }
 printf("Waking up ...\n");
 exit(0);
}