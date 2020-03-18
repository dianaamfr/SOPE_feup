//=====================================================================
// OPERATING SYSTEMS / MIEIC / FEUP - Jorge Silva
// Signals - s02.c
// Illustrating some asynchronous signals
// Ignoring SIGINT
// try to kill this process using:
// 1) CTRL-C
// 2) "kill" from another terminal window
//---------------------------------------------------------------------
#include <stdio.h>
#include <signal.h>
int main(void)
{
 signal(SIGINT,SIG_IGN);
 printf("I'm going to work very hard !\n");
 for (;;); // Doing some "work" that never ends
 return 0;
}
/*
/usr/users1/dei/jsilva/sope/signals> ./s2
I'm going to work very hard !
^C
^C
^C
Terminated <------- "kill PID" executed from another terminal
/usr/users1/dei/jsilva/sope/signals>
/usr/users1/dei/jsilva/sope/signals> echo $?
143
/usr/users1/dei/jsilva/sope/signals>
*/ 