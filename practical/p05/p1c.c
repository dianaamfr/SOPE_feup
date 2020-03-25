#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1
#define MAX_NUM_SIZE 10

int main(void){
   int fd[2];
   pid_t pid;

   pipe(fd);

   pid = fork();

   if(pid > 0){ //parent
      char a[2][MAX_NUM_SIZE];
      
      printf("x y ? ");
      scanf("%s %s", a[0],a[1]);

      close(fd[READ]);
      write(fd[WRITE],a,2*sizeof(char)*MAX_NUM_SIZE); //envia‐os números inteiros lidos do teclado ao processo‐filho, através de um pipe
      close(fd[WRITE]);

   }
   
   else if(pid == 0){ //child
      char b[2][MAX_NUM_SIZE];

      close(fd[WRITE]); 
      read(fd[READ],b,2*sizeof(char)*MAX_NUM_SIZE);
      printf("x + y = %d\n", atoi(b[0])+atoi(b[1])); 
      printf("x - y = %d\n", atoi(b[0])-atoi(b[1])); 
      printf("x * y = %d\n",atoi(b[0])* atoi(b[1])); 
      printf("x + y = "); 
      if(atoi(b[1]) != 0){
         float f = (float)atoi(b[0]) / atoi(b[1])  ;
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