//=====================================================================
// OPERATING SYSTEMS / MIEIC / FEUP - Jorge Silva
// Signals - s05.c
// SIGKILL can't be caught ...
// try to kill this process using:
// 1) CTRL-C
// 2) "kill" from another terminal window
//---------------------------------------------------------------------
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
void sigkill_handler(int signo)
{
 printf("SIGKILL received by process %d...!\n", getpid());
}
int main(void)
{
 signal(SIGINT,SIG_IGN);
 signal(SIGTERM,SIG_IGN);
 if (signal(SIGKILL,sigkill_handler) == SIG_ERR)
 {
   printf("signal(SIGKILL,sigkill_handler) = SIG_ERR because SIGKILL can't be caught ...!\n");
   exit(1);
 };
 printf("I'm going to work very hard !\n");
 for (;;); // Doing some "work" that never ends
 return 0;
}
/*
/usr/users1/dei/jsilva/sope/signals> ./s05
SIGKILL can't be caught ...!
/usr/users1/dei/jsilva/sope/signals>
*/ 