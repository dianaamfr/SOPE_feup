// PROGRAMA p02a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h> 

void sigint_handler(int signo)
{
 printf("Entering SIGINT handler ...\n");
 sleep(10);
 printf("Exiting SIGINT handler ...\n");
} 
                                                                             
int main(void)
{
   struct sigaction action;
   action.sa_handler = sigint_handler;
   sigemptyset(&action.sa_mask);
   action.sa_flags = 0;
   if (sigaction(SIGINT,&action,NULL) < 0)
   {
      fprintf(stderr,"Unable to install SIGINT handler\n");
      exit(1);
   }
   printf("Try me with CTRL-C ...\n");
   while(1) pause();
   exit(0);
} 

/*
) Tecle várias vezes CTRL‐C durante a execução.
Quantas ocorrências do sinal SIGINT foram processadas?

Ao pressionar a 1ª vez o handler é executado e faz um sleep de 10 segundos. Se vários ^C 
forem executados nesse intervalo apena um é guardado e executado quando o handler termina para o ^C anterior
*/