//======================================================================
// e01_aux.c / JAS
// To be executed with e01.c
//----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
int i, n;
n = atoi(argv[1]);
for (i=1; i<=n; i++)
{
printf("CHILD (%d - %d): Hello father ...%d!\n",getpid(),getppid(),i);
}
return 10;
}