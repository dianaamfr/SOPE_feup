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
Usando o comando kill da shell, envie, a partir de outra janela de terminal, o sinal SIGTERM ao
processo, durante o ciclo de espera no interior do handler. Verifique o que acontece e interprete o
resultado.

O programa termina com código de terminação 143 (SIGTERM). Não existe nenhum handler para sigterm logo o programa termina.

*/