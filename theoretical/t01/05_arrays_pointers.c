//Arrays of strings
//passing an array as parameter
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME_LENGTH 20
#define MAX_NAMES 3

 /*void show(char nms[][MAX_NAME_LENGTH], int n)
{
   int i;
   for (i = 0; i < n; i++)
      printf("%s\n", nms[i]);
}

int main()
{
   char names[MAX_NAMES][MAX_NAME_LENGTH];
   strcpy(names[0], "Ann"); // How many chars were allocated for this name? => 4 (3+'/0')
   strcpy(names[1], "John Dalton");
   show(names, 2);
   return 0;
} */

//======================
/* void show(char *nms[], int n) // NOTE THE DIFFERENCE FROM PREVIOUS EXAMPLE
{
   // EXPLAIN THE COMPILATION WARNING
   //expected ‘char **’ but argument is of type ‘char (*)[20]’
   int i;
   for (i = 0; i < n; i++)
      printf("%s\n", nms[i]);
}

int main()
{
   char names[MAX_NAMES][MAX_NAME_LENGTH];
   strcpy(names[0], "Ann");
   strcpy(names[1], "John Dalton");
   show(names, 2);
return 0;
} */

//================================================================================
void show(char *nms[], int n)
// void show(char **nms, int n)
{
   int i;
   for (i = 0; i < n; i++)
      printf("%s\n", nms[i]);
}
// ALTERNATIVE
int main()
{
   char *names[MAX_NAMES];
   int i;

   for (i = 0; i < MAX_NAMES; i++)
      names[i] = (char *)malloc(MAX_NAME_LENGTH*sizeof(char));

   strcpy(names[0], "Ann");
   strcpy(names[1], "John Dalton");
   show(names, 2);

   for (i = 0; i < MAX_NAMES; i++)
      free(names[i]);
   return 0;
}