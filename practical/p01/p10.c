#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE 100

int main(){
   char in[MAX_LINE_SIZE];
   char *token;
   char **tokens;

   tokens = (char**)malloc(1000*sizeof(char));

   fgets(in, MAX_LINE_SIZE,stdin);

   /* get the first token */
   tokens[0] = (char*)malloc(MAX_LINE_SIZE*sizeof(char));
   token = strtok(in, " ");
   tokens[0] = token;
   
   /* walk through other tokens */
   int i=1;
   while( token != NULL ){
      tokens[i] = (char*)malloc(MAX_LINE_SIZE*sizeof(char));
      token = strtok(NULL, " ");
      tokens[i] = token;
      i++;
   }

   for(unsigned int j=0; tokens[j] != NULL; j++){
      for(unsigned int i=0; i< strlen(tokens[j]); i++){
         if(tokens[j][i] =='|' || tokens[j][i] ==';')
            printf("\n");
         else
            printf("%c",tokens[j][i]);
         
      }
      printf(" ");
   }
   return 0;
}