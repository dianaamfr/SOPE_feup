//=====================================================================
// OPERATING SYSTEMS / MIEIC / FEUP - Jorge Silva
// Signals – s06.c
// Illustrating some asynchronous signals
// try to kill this process using:
// 1) CTRL-C
// 2) "kill" from another terminal window
//---------------------------------------------------------------------
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signo)
{
 printf("\nI can't be CTRL-C'ed :)\n");
 sleep(5);
}
int main(void)
{
 signal(SIGINT,sigint_handler);
 printf("I'm going to work very hard !\n");
 for (;;); // Doing some "work" that never ends
 return 0;
}