//======================================================================
// THREADS - examples
// t09.c
// Passing arguments to threads
// The solution to the "passing arguments to the threads" problem:
// allocate space for the arguments in the heap
//----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10

void *printHello(void *threadId)
{
   printf("Thread %2d: Hello World!\n", *(int *) threadId);
   free(threadId);
   pthread_exit(NULL);
}

int main()
{
   pthread_t tid[NUM_THREADS];
   int rc, t;
   int *thrArg;

   for(t=1; t<= NUM_THREADS; t++){
      printf("Creating thread %d\n", t);
      thrArg = (int *) malloc(sizeof(t));
      *thrArg = t;
      rc = pthread_create(&tid[t-1], NULL, printHello, thrArg);

      if (rc)
      {
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(1);
      }
   }
   pthread_exit(NULL);
}
//TO DO: modify in order to free the memory allocated in the heap

