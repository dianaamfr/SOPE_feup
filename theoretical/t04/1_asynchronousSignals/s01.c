//=====================================================================
// OPERATING SYSTEMS / MIEIC / FEUP - Jorge Silva
// Signals - s01.c
// Illustrating some asynchronous signals
// Kill this process using:
// 1) CTRL-C
// 2) "kill" from another terminal window
//---------------------------------------------------------------------
#include <stdio.h>
int main(void)
{
 printf("I'm going to work very hard !\n");
 for (;;); // Doing some "work" that never ends
 return 0;
} 