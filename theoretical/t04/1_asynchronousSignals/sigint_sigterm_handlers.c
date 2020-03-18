//=====================================================================
// OPERATING SYSTEMS / MIEIC / FEUP - Jorge Silva
// Signals – s08.c
// Illustrating some asynchronous signals
// Installing a handler for SIGINT & SIGTERM
// How to end this process ?
// - "kill" from another terminal (sends SIGTERM)
// Try with "kill -KILL pid"
//---------------------------------------------------------------------
#include <stdio.h>
#include <signal.h>
void sigint_handler(int signo)
{
 printf("SIGINT received ... \n");
 return;
}
void sigterm_handler(int signo)
{
 printf("SIGTERM received ... \n");
 return;
}
int main(void)
{
 // installing handler for CTRL-C signal (SIGINT)
 signal(SIGINT,sigint_handler);
 // installing handler for default "kill" command action (SIGTERM)
 signal(SIGTERM,sigterm_handler);
 //signal(SIGTERM,SIG_IGN);
 printf("I'm going to work very hard !\n");
 for (;;); // Doing some "work" that never ends
 return 0;
} 