//Illustrating some asynchronous signals 
//Handling SIGUSR1 and SIGUSR2 with the same handler
//Kill this process using:
// 1) CTRL-C
// 2) "kill" from another terminal window 


#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void sig_usr(int); /* o mesmo handler para os 2 sinais */
int main(void)
{
   if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
      fprintf(stderr, "can't catch SIGUSR1\n");
      exit(1);
   }
   if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
      fprintf(stderr, "can't catch SIGUSR2\n");
      exit(1);
   }
   for ( ; ; )
   pause();
}
static void sig_usr(int signo) /* o argumento indica o sinal recebido */
{
   if (signo == SIGUSR1)
      printf("received SIGUSR1\n");
   else if (signo == SIGUSR2)
      printf("received SIGUSR2\n");
   else {
      fprintf(stderr, "received signal %d\n", signo);
      exit(2);
   }
   return;
} 

/*
$ gcc -Wall sigusr_handler.c
$ ./a.out &                      -> iniciar o processo em background
[1] 4720                         -> a job-control shell escreve o nº do job e a PID do proc.
$ kill -USR1 4720                -> enviar-lhe SIGUSR1
Received SIGUSR1                 -> escrito pelo signal handler

$ ./a.out &                      
$ kill -USR2 4720                -> enviar-lhe SIGUSR2
Received SIGUSR2                 -> escrito pelo signal handler

$ ./a.out &
$ kill 4720                      -> enviar SIGTERM ao processo
[1] Terminated a.out             -> o processo foi terminado,
                                    dado que não trata o sinal e
                                    a acção por omissão é a terminação
*/