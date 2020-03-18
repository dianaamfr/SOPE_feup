//=====================================================================
// OPERATING SYSTEMS / MIEIC / FEUP - Jorge Silva
// Signals - s04.c
// Illustrating some asynchronous signals
// SIGKILL can't be ignored ...
// try to kill this process using:
// 1) CTRL-C
// 2) "kill" from another terminal window
//---------------------------------------------------------------------
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
int main(void)
{
 signal(SIGINT,SIG_IGN);
 signal(SIGTERM,SIG_IGN);
 if (signal(SIGKILL,SIG_IGN) == SIG_ERR) // should allways test SIG_ERR ...
 {
 printf("signal(SIGKILL,SIG_IGN) = SIG_ERR because SIGKILL can't be ignored ...!\n");
 exit(1);
 };
 printf("I'm going to work very hard !\n");
 for (;;); // Doing some "work" that never ends
 return 0;
}
/*
/usr/users1/dei/jsilva/sope/signals> ./s04
SIGKILL can't be ignored ...!
/usr/users1/dei/jsilva/sope/signals>
*/ 