#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(void)
{
   int fork_return_value;
   printf("before fork...\n");

   fork_return_value = fork();
   printf("I'm process %d: 'fork_return_value'=%d. My parent is %d.\n\n",getpid(),fork_return_value,getppid());
   return 0;
}