#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[], char* envp[])
{
   for (unsigned int i=0; envp[i]!= NULL; i++){
      if(strncmp(envp[i],"USER=",5) == 0){
         printf("Hello %s!\n",envp[i]+5);
         break; 
      }
   } 

   return 0;
}