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
      printf("Creating thread %d\n", t); // Prints for every thread
      rc = pthread_create(&tid[t-1], NULL, printHello, &t);
      if (rc)
      {
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(1);
      }
   }
   pthread_exit(NULL);
} 

/*
Sometimes the Hello World message is not shown - for the first 2 threads.
t is a local variable.

PASSAGEM INCORRECTA DE ARGUMENTOS:
o ciclo que cria os threads modifica
o conteúdo do endereço passado como argumento
possivelmente antes de o thread criado conseguir aceder-lhe

Output possivel:

Creating thread 0
Hello from thread no. 1!
Creating thread 1
Creating thread 2
Hello from thread no. 2!
Creating thread 3
Creating thread 4
Hello from thread no. 4!
Hello from thread no. 4!
Creating thread 5
Hello from thread no. 5!
Creating thread 6
Creating thread 7
Hello from thread no. 7!
Hello from thread no. 7!
Creating thread 8
Hello from thread no. 8!
Creating thread 9
Hello from thread no. 10!
Hello from thread no. 10! 
*/