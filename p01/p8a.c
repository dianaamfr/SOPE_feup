#include <stdlib.h>
#include <unistd.h> 
#include <stdio.h>
#include <sys/times.h>
#include<time.h>

int main(int argc, char* argv[]){
   int n1 = atoi(argv[1]);
   int n2 = atoi(argv[2]);
   int n = n2-1;
   clock_t start,end;
   struct tms t;
   long ticks;

   srand(time(NULL));
   start = times(&t); /*start measuring time*/

   ticks = sysconf(_SC_CLK_TCK);

   while(n != n2){
      n = (rand()%(n1+1));
      printf("%d\n",n);
   }

   printf("\nClock ticks per second: %ld\n", ticks);

   end = times(&t); /*end measuring time*/

   printf("Clock: %4.2f s\n", (double)(end-start)/ticks);
   /*The first number after the % sign is the number of
   spaces allocated for the number to be printed. 
   The second number, which comes after the dot, is the 
   specifier of the number of digits after decimal point 
   for the number to be printed*/
   printf("User time: %4.6f s\n", (double)t.tms_utime/ticks);
   printf("System time: %4.6f s\n", (double)t.tms_stime/ticks);

   return 0;
}