#include <stdio.h>

#define MAX_NAME_SIZE 40
int main(void)
{
   char name[MAX_NAME_SIZE];

   printf("What's you name? ");
   fgets(name,MAX_NAME_SIZE,stdin);

   for(unsigned int i=0; i< MAX_NAME_SIZE; i++){
      if(name[i] ==  '\n'){
         name[i] = '\0';
         break;
      }
   }

   printf("Hello %s!\n",name);
   return 0;
} 
