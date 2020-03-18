//=====================================================================
// OPERATING SYSTEMS / MIEIC / FEUP - Jorge Silva
// Signals - s03.c
// Illustrating some asynchronous signals
// Ignoring SIGINT and SIGTERM
// Try to kill this process using:
// 1) CTRL-C
// 2) "kill" from another terminal window
//---------------------------------------------------------------------
#include <stdio.h>
#include <signal.h>
int main(void)
{
 signal(SIGINT,SIG_IGN);
 signal(SIGTERM,SIG_IGN);
 printf("I'm going to work very hard !\n");
 for (;;); // Doing some "work" that never ends
 return 0;
}
/*
/usr/users1/dei/jsilva/sope/signals> ./s3
I'm going to work very hard ! 
Killed <------------ "ps u" + "kill -KILL PID" from another terminal
/usr/users1/dei/jsilva/sope/signals> echo $?
137
/usr/users1/dei/jsilva/sope/signals>
*/ 