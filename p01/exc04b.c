#include <stdio.h>

#define MAX_NAME_SIZE 40
int main(void)
{
   char name[MAX_NAME_SIZE];
   int n=0;

   printf("What's you name? ");
   fgets(name,MAX_NAME_SIZE,stdin);

   printf("Choose a number? ");
   scanf("%d",&n);

   for(unsigned int i=0; i< MAX_NAME_SIZE; i++){
         if(name[i] ==  '\n'){
            name[i] = '\0';
            break;
         }
      }

   if(n > 0){
      for(unsigned int i=0; i<n; i++)
         printf("%d) Hello %s!\n",i+1,name);
   }

   return 0;
} 
