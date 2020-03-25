#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

int main(void){
   int fd[2];
   pid_t pid;

   pipe(fd);

   pid = fork();

   if(pid > 0){ //parent
      int a[2];
      printf("x y ? ");
      scanf("%d %d", &a[0],&a[1]);
      close(fd[READ]);
      write(fd[WRITE],a,2*sizeof(int)); //envia‐os números inteiros lidos do teclado ao processo‐filho, através de um pipe
      close(fd[WRITE]);
   }
   
   else if(pid == 0){ //child
   int b[2];
      close(fd[WRITE]); 
      read(fd[READ],b,2*sizeof(int));
      printf("x + y = %d\n", b[0]+b[1]); 
      printf("x - y = %d\n", b[0]-b[1]); 
      printf("x * y = %d\n", b[0]*b[1]); 
      printf("x + y = "); 
      if(b[1] != 0){
         float f = (float)b[0] / b[1];
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