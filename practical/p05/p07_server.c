/* 
 Arquitectura cliente-servidor
 Programa servidor
 O cliente envia os números lidos do ecrã ao servidor (processo‐calculador)
 e o servidor devolve-lhe os resultados.

O processo‐servidor deve manter‐se em funcionamento até que os números a processar
sejam ambos iguais a zero, situação em que não deve efectuar qualquer cálculo, mas apenas deve destruir
os dois FIFOS
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <signal.h>
#include <errno.h>
#include <string.h> 

int main(){
   int fd1, fd2, operands[2];

   if(mkfifo("/tmp/fifo_req",0660) < 0){
      if (errno == EEXIST)
         printf("FIFO '/tmp/fifo_req' already exists\n");
      else printf("Can't create FIFO\n"); 
   }
   else 
      printf("FIFO '/tmp/fifo_req' sucessfully created\n"); 

   if(mkfifo("/tmp/fifo_ans",0660) < 0){
      if (errno == EEXIST)
         printf("FIFO '/tmp/fifo_ans' already exists\n");
      else printf("Can't create FIFO\n"); 
   }
   else 
      printf("FIFO '/tmp/fifo_ans' sucessfully created\n");

   do{
      if ((fd1 = open("/tmp/fifo_req",O_RDONLY)) != -1)
         printf("FIFO '/tmp/fifo_req' openned in READONLY mode\n");

      read(fd1,&operands,2 * sizeof(int));
      close(fd1);

      if (operands[0] != 0 || operands[1] != 0) {
         float results[5];
         float inf = 1;
         if(operands[1] != 0)
            inf = 0;
         
         results[0] = operands[0] + operands[1];
         results[1] = operands[0] - operands[1];
         results[2] = operands[0] * operands[1];
         
         if(inf != 0)
            results[3] = operands[0] / (float)operands[1];
         else
            results[3] = 0;
         results[4] = inf;

         if ((fd2 = open("/tmp/fifo_ans",O_WRONLY)) != -1)
            printf("FIFO '/tmp/fifo_ans' openned in WRITEONLY mode\n");

         write(fd2, results, 5 * sizeof(float));
         close(fd2);
      }
   } while (operands[0] != 0 || operands[1] != 0); 

   close(fd1);
   close(fd2); 

   if (unlink("/tmp/fifo_req") < 0 || unlink("/tmp/fifo_ans") < 0)
      printf("Error when destroying FIFOS'\n");
   else
      printf("FIFOS destroyed\n");

   exit(0); 
}