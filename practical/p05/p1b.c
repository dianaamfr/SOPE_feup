#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

struct integers{
   int a;
   int b;
};

int main(void){
   int fd[2];
   pid_t pid;

   pipe(fd);

   pid = fork();

   if(pid > 0){ //parent
      struct integers values;
      printf("x y ? ");
      scanf("%d %d", &values.a,&values.b);
      close(fd[READ]);
      write(fd[WRITE],&values,2*sizeof(int)); //envia‐os números inteiros lidos do teclado ao processo‐filho, através de um pipe
      close(fd[WRITE]);
   }
   
   else if(pid == 0){ //child
      struct integers values2;
      close(fd[WRITE]); 
      read(fd[READ],&values2,2*sizeof(int));
      printf("x + y = %d\n", values2.a + values2.b); 
      printf("x - y = %d\n", values2.a - values2.b); 
      printf("x * y = %d\n", values2.a * values2.b); 
      printf("x / y = "); 
      if(values2.b != 0){
         float f = (float) values2.a / values2.b;
         printf("%f\n", f); 
      }
      else 
         printf("inf\n");
      
      close(fd[READ]);
   }

   else{ //error
      fprintf(stderr,"Fork error!\n");
      exit(1);
   }
   return 0;
}