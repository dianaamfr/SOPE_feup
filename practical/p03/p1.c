#include <stdio.h>
#include <unistd.h>

int global=1;

//imprime pid e ppid do processo pai, incrementa global e decrementa local no processo pai
//imprime pid atual(pai) e as variaveis atualizadas por ele (global = 2 ; local = 1 )
//imprime pid e ppid(igual ao pid anterior) do processo filho, decrementa global e incrementa local no processo filho
//imprime pid atual(filho) e as variaveis atualizadas por ele (são mudadas a partir 
//das iniciais nao tendo as mudanças do pai - temos uma copia de cada avriavel, uma usada em cada processo) (global = 0 ; local = 3 )

int main(void) {
   int local = 2;

   if(fork() > 0) { // >0 => processo pai
      printf("PID = %d; PPID = %d\n", getpid(), getppid()); //getpid() returns the process ID (PID) of the calling process
                                                            //getppid() returns the process ID of the parent of the calling  process.
      global++;
      local--;
   } else { //processo filho
      printf("PID = %d; PPID = %d\n", getpid(), getppid());
      global--;
      local++;
   }
   printf("PID = %d - global = %d ; local = %d\n", getpid(), global, local); //ambos os processos executam o printf final
   return 0;
} 