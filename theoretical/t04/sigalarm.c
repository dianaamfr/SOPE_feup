//=====================================================================
// OPERATING SYSTEMS / MIEIC / FEUP - Jorge Silva
// Signals - s13.c
// Installing a handler for SIGALRM
// An example of a race condition
//---------------------------------------------------------------------
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
int alarmflag = 0;
void alarmhandler(int signo)
{
 printf("Alarm received ...\n");
 alarmflag = 1;
}
int main(void)
{
 signal(SIGALRM, alarmhandler);
 alarm(5);
 printf("Pausing ...\n");
 if (!alarmflag) pause(); // RACE CONDITION ...!
 printf("Ending ...\n");
 exit(0);
} 