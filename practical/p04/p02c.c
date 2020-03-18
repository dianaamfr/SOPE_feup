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

void sigterm_handler(int signo)
{
 printf("Entering SIGTERM handler ...\n");
 sleep(10);
 printf("Exiting SIGTERM handler ...\n");
} 
                                                                             
int main(void)
{
   struct sigaction action, action2;

   action.sa_handler = sigint_handler;
   sigemptyset(&action.sa_mask);
   action.sa_flags = 0;
   if (sigaction(SIGINT,&action,NULL) < 0)
   {
      fprintf(stderr,"Unable to install SIGINT handler\n");
      exit(1);
   }

   action2.sa_handler = sigterm_handler;
   sigemptyset(&action2.sa_mask);
   action2.sa_flags = 0;
   if (sigaction(SIGTERM,&action2,NULL) < 0)
   {
      fprintf(stderr,"Unable to install SIGTERM handler\n");
      exit(1);
   }

   printf("Try me with CTRL-C ...\n");
   while(1) pause();
   exit(0);
} 

/*
Instale também um handler para o sinal SIGTERM (este handler deve apenas escrever mensagens de
entrada e de saída do handler). Tecle várias vezes em CTRL‐C durante a execução e envie o sinal SIGTERM
ao processo durante o período em que o handler de SIGINT está a ser executado. Interprete os resultados.

O handler do SIGTERM é chamado dentro do handler do SIGINT sendo que quando o do SIGTERM termina de executar o do SIGINT continua
*/