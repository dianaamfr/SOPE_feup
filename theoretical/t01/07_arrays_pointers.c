// String array Dinamically allocate memory

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 10

void readNames(char **nms, int n)
{
   int i;
   for (i = 0; i < n; i++)
   {
      printf("Name [%d] ? ", i + 1);
      fgets(nms[i], MAX_NAME_LENGTH, stdin);
   }
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

   for (i = 0; i < n; i++)
      names[i] = (char *)malloc(MAX_NAME_LENGTH*sizeof(char));
   // The space allocated for each name is fixed ... :‐(
   // TO DO BY STUDENTS: allocate only the necessary space for each name

   // Read the names
   readNames(names, n);

   // Show the names
   showNames(names, n);
   
   // Free the dinamically allocated memory
   for (i = 0; i < n; i++)
      free(names[i]);
   free(names);
   
   return 0;
}