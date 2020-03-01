// String array Dinamically allocate memory

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 10

char* dynamicAllocateString() {
    char *str = NULL; 
    int j = 2, c;

    str = (char*)malloc(sizeof(char)); // espaço para um caracter

    while((c = getchar()) && c != '\n')
    {
        str[j-2] = c;//guarda caracter no espaço que tem
        str = realloc(str,j*sizeof(char)); // guarda espaço para +1 caracter (o proximo)

        j++;
    }
    str[j-2] = '\0'; //guarda o simbolo do caracter final da palavra
    return str;
}

void showNames(char **nms, int n)
{
   int i;
   for (i = 0; i < n; i++)
      printf("%s", nms[i]);
}

int main()
{
   char **names;
   int i, n;
   printf("How many names ? ");
   scanf("%d", &n);
   while (getchar() != '\n'); //fflush(stdin);

   // Dinamically allocate memory
   names = (char **)malloc(n*sizeof(char *));

   for (i = 0; i < n; i++){
      printf("Name [%d] ? ", i + 1);
      names[i] = dynamicAllocateString();
   }
  
   // Show the names
   showNames(names, n);
   
   // Free the dinamically allocated memory
   for (i = 0; i < n; i++)
      free(names[i]);
   free(names);
   
   return 0;
}