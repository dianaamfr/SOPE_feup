#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
   char s1[] = "Hello ";
   char s2[] = "my ";
   char s3[] = "friends!";
   pid_t pid;

   for(int i=0;i<3;i++){
      pid = fork();
      if(pid == 0){
         switch (i)
         {
         case 0:
            write(STDOUT_FILENO,s1,6);
            break;
         case 1:
            write(STDOUT_FILENO,s2,3);
            break;
         case 2:
            write(STDOUT_FILENO,s3,8);
            break;
         default:
            break;
         }
         break;
      }
   }
}