// PROGRAMA p2.c
#include <unistd.h>
#include <stdio.h>

int main(void) {
   //(a)
   /*write(STDOUT_FILENO,"1",1); 

   if(fork() > 0) { //processo pai
      write(STDOUT_FILENO,"2",1);
      write(STDOUT_FILENO,"3",1);
   } else { //processo filho ou erro
      write(STDOUT_FILENO,"4",1);
      write(STDOUT_FILENO,"5",1);
   }
   write(STDOUT_FILENO,"\n",1); //ambos*/

   //(b)
   printf("1");
   printf("\n"); //(c)

   if(fork() > 0) { //processo pai
      printf("2");
      printf("3");
   } else { //processo filho ou erro
      printf("4");
      printf("5");
   }
   printf("\n");

   return 0;
}

/*(a) write -> diferentes line buffers do kernel

The parent will be executed first (prints 123)
The son process will be executed after the parent and will use a new kernel buffer so it does not print the first "1"
The new line is written in both processes because after a fork, everything that is not inside the if/else is executed by both (código é duplicado para os dois processos)

123 
45
*/


/* (b) printf -> o mesmo line buffer 

   The parent will be executed first but, when the son starts executing, the buffer used will be a duplicate of the parent buffer that did not flush the "1"  

 Flushing what is pending on buffer can be done by printing a new line: printf("\n");
 So, since we have not printed a newline after the 1, it will remain in the parent buffer

 123
 145
*/

/* (c) printg and new line so the 1 doesn't remain in the buffer for the son process

1
23
45 
*/