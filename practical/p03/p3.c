#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MAX 50

//inicialmente, o fork(), isto é, a criação de um processo filho demora algum tempo, pelo que o primeiro processo que o kernel executa é o do pai
//Ou seja, quando o processo filho começa a executar já foram impressos no ecrã vários numeros positivos pelo processo filho
//Quando o processo filho está pronto a executar o kernel opta por alternar entre os dois processos
//quando este executa começa do zero pois ele usa o valor da variável quando o fork foi chamado (nessa chamada há duplicação do código)

int main(void) {
   int i;
   pid_t pid;
   char str[10];

   pid=fork();

   switch (pid){
      case -1: //erro
         perror("fork");
         break;
      case 0: //filho
         for (i=1; i<=MAX; i++) {
            sprintf(str,"-%d",i);
            write(STDOUT_FILENO,str,strlen(str));
         }
      break;
      default: //pai
         for (i=1; i<=MAX; i++) {
            sprintf(str,"+%d",i);
            write(STDOUT_FILENO,str,strlen(str));
         }
      }


   return 0;
} 