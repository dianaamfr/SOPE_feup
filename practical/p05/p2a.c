#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

struct integers{
   int sum;
   int sub;
   int prod;
   float div;
   int invalid;
};

int main(void){
   int fd1[2], fd2[2];
   pid_t pid;

   pipe(fd1);
   pipe(fd2);

   pid = fork();

   if(pid > 0){ //parent
      int a[2];
      struct integers results1;

      printf("x y ? ");
      scanf("%d %d", &a[0],&a[1]);

      close(fd1[READ]);
      close(fd2[WRITE]);
      write(fd1[WRITE],a,2*sizeof(int)); //envia‐os números inteiros lidos do teclado ao processo‐filho, através de um pipe
      close(fd1[WRITE]);

      read(fd2[READ],&results1,sizeof(float)*4);
      close(fd2[READ]);

      printf("x + y = %d\n", results1.sum); 
      printf("x - y = %d\n", results1.sub); 
      printf("x * y = %d\n", results1.prod); 
      printf("x / y = "); 
      if(results1.invalid != 0){
         printf("%f\n", results1.div); 
      }
      else 
         printf("inf\n");

   }
   
   else if(pid == 0){ //child
      int b[2];
      struct integers results2;
      
      close(fd1[WRITE]); 
      close(fd2[READ]);
      read(fd1[READ],b,2*sizeof(int));

      results2.sum = b[0]+b[1];
      results2.sub = b[0]-b[1];
      results2.prod = b[0]*b[1];

      if(b[1] != 0){
         float f = (float)b[0] / b[1];
         results2.div = f; 
      }
      
      close(fd1[READ]);

      write(fd2[WRITE],&results2,sizeof(float)*4);
      close(fd2[WRITE]);
   }

   else{ //error
      fprintf(stderr,"Fork error!\n");
      exit(1);
   }
   return 0;
}