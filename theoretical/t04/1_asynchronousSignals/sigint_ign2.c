#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
   void (*oldhandler)(int);
   
   printf("I can be Ctrl-C’ed\n");
   sleep(5);
   oldhandler = signal(SIGINT, SIG_IGN);
   printf("I’m protected from Ctrl-C now \n");
   sleep(5);
   signal(SIGINT, oldhandler);
   printf("I’m vulnerable again!\n");
   sleep(5);
   printf("Bye.\n");
   exit(0);
}