//=====================================================================
// OPERATING SYSTEMS / MIEIC / FEUP - Jorge Silva
// Signals - s15.c
// Installing a handler for CTRL-C and returning to default handler
//---------------------------------------------------------------------
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
int main(void)
{
 struct sigaction action, orig_action;
 printf("I can be CTRL-C'ed\n");
 sleep(5);
 // prepare the 'sigaction struct' for ignoring SIGINT
 action.sa_handler = SIG_IGN;
 sigemptyset(&action.sa_mask);
 action.sa_flags = 0;
 // ignore SIGINT and get the original handler
 sigaction(SIGINT,&action,&orig_action);
 printf("\nI'm protected from Ctrl-C now \n");
 sleep(5);
 // set the original handler
 sigaction(SIGINT,&orig_action,NULL);
 printf("\nI'm vulnerable again!\n");
 sleep(5);
 printf("Bye.\n");
 exit(0);
} 