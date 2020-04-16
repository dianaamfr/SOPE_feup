/* 
 Arquitectura cliente-servidor
 Programa cliente
 O cliente lê os números do ecrã, informa o sevidor e apresenta os resultados dos cálculos, fornecidos pelo servidor após o cálculo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h> 

int main(){

   int fd1, fd2, operands[2];
   float results[5];

   printf("x y ? ");
   scanf("%d %d", &operands[0],&operands[1]);

   fd1 = open("/tmp/fifo_req",O_WRONLY);
   if (fd1 == -1) {
      printf("Oops !!! Service is closed !!!\n");
      exit(1);
   }

   write(fd1,operands,2*sizeof(int));
   close(fd1); 

   if(operands[0] != 0 || operands[1] != 0){

      if ((fd2 = open("/tmp/fifo_ans",O_RDONLY)) != -1)
         printf("FIFO '/tmp/fifo_ans' openned in READONLY mode\n");

      read(fd2,&results,5 * sizeof(float));
      close(fd2);

      printf("x + y = %f\n", results[0]); 
      printf("x - y = %f\n", results[1]); 
      printf("x * y = %f\n", results[2]); 
      printf("x / y = "); 
      if(results[4] == 0)
         printf("%f\n", results[3]); 
      else
          printf("inf\n");
      
   }
   
   exit(0);
}