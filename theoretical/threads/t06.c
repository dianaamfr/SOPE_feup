//======================================================================
// THREADS - examples
// t06.c
// Passing arguments to threads - BE CAREFUL !!!
//----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10

void *printHello(void *threadId)
{
   printf("Thread %2d: Hello World!\n", *(int*)threadId);
   pthread_exit(NULL);
}
int main()
{
   pthread_t tid[NUM_THREADS];
   int rc, t; 
   
   for(t=1; t<= NUM_THREADS; t++){
      printf("Creating thread %d\n", t);
      rc = pthread_create(&tid[t-1], NULL, printHello, &t);
      if (rc)
      {
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(1);
      }
   }
   pthread_exit(NULL);
} 