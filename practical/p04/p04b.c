// PROGRAMA p04a.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

int main(void)
{
   pid_t pid;
   int i, n, status;

   for (i=1; i<=3; i++) {
      pid=fork(); 
   
      if (pid == 0){
         printf("CHILD no. %d (PID=%d) working ... \n",i,getpid());
         sleep(i*7); // child working ...
         printf("CHILD no. %d (PID=%d) exiting ... \n",i,getpid());
         exit(0);
      }
   }

   for (i=1 ;i <= 4; i++) {
      printf("PARENT %d: working hard (task no. %d) ...\n",getpid(),i);

      n=20; while((n=sleep(n))!=0);

      printf("PARENT: end of task no. %d\n",i);
      printf("PARENT: waiting for child no. %d ...\n",i);

      pid = waitpid(-1,&status,WNOHANG);
      if (pid != -1)
         printf("PARENT: child with PID=%d terminated with exit code %d\n",pid,WEXITSTATUS(status));
   }
   exit(0);
} 

/*
Se teclar ^C depois de os filhos serem criados na própria consola, como o tratamento dos sinais é herdado pelos processos-filhos (neste caso o tratamento default to ^C) termina a execução de todos os processos.
Caso envie ao processo pai o sinal SIGINT pela consola, é atribuído aos processos filhos um novo pai, continuando estes a executar.
*/