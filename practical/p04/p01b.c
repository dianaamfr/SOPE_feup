// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
void sigint_handler(int signo)
{
 printf("In SIGINT handler ...\n");
}

void sigusr_handler(int signo)
{
 printf("In SIGUSR handler ...\n");
}

int main(void)
{
 if (signal(SIGINT,sigint_handler) < 0)
 {
   fprintf(stderr,"Unable to install SIGINT handler\n");
   exit(1);
 }
 if (signal(SIGUSR1,sigusr_handler) < 0)
 {
   fprintf(stderr,"Unable to install SIGUSR handler\n");
   exit(1);
 }
 printf("Sleeping for 30 seconds ...\n");
 unsigned int timeLeft = 30;
 while(timeLeft > 0){
    timeLeft=sleep(timeLeft);
 }
 printf("Waking up ...\n");
 exit(0);
}

/*
sleep()  causes  the calling thread to sleep either until the number of
real-time seconds specified in seconds have elapsed or UNTIL A SIGNAL ARRIVES WHICH IS NOT IGNORED.
*/