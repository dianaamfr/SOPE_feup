//=====================================================================
// OPERATING SYSTEMS / MIEIC / FEUP - Jorge Silva
// Signals - s14.c
// POSIX signals APIs
// Installing a handler for SIGINT
// IMPORTANT NOTE:
// You should always use POSIX APIs.
// signal() call is deprecated
// It was used in the previous exemples
// because it is easier to introduce the signal concepts
//---------------------------------------------------------------------
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void sigint_handler(int sig) {
 printf("AUUU! Received signal %d\n",sig);
}
int main(void)
{
 struct sigaction action;
 // prepare the 'sigaction struct'
 action.sa_handler = sigint_handler;
 sigemptyset(&action.sa_mask);
 action.sa_flags = 0;
 // install the handler
 sigaction(SIGINT,&action,NULL);
 while(1)
 {
 printf("Hello !\n"); sleep(1);
 }
 exit(0);
} 