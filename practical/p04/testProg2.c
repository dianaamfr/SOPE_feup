#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
   char name[] = "USER";
   printf("Larara %s!\n",getenv(name));

   return 0;
}
