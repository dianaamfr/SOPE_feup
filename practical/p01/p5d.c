#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//NOTES: SET {envVar} environment variables with export (in console), print them with printev {envVar}

int main(int argc, char* argv[])
{
   char name[] = "USER_NAME";
   printf("Hello %s!\n",getenv(name));

   return 0;
}