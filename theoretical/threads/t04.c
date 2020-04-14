//======================================================================
// THREADS - examples
// t04.c
// - Passing info bidirectionally, using global variables
// - Waiting for the end of a thread (alternative: use sync. mechan.)
//----------------------------------------------------------------------
#include <stdio.h>
#include <pthread.h>
int global;
void *thr_func(void *arg)
{
 global = 20;
 printf("Aux thread: %d\n", global);
 return NULL;
}
int main(void)
{
 pthread_t tid;
 global = 10;
 printf("Main thread: %d\n", global);
 pthread_create(&tid, NULL, thr_func, NULL);

 /*o thread principal esperou que o thread auxiliar terminasse */
 pthread_join(tid, NULL);
 printf("Main thread: %d\n", global);

 /*o programa pode terminar sem problema */
 return 0;
}

/*Um thread pode esperar que outros threads terminem
usando a chamada pthread_join().

O thread que invocar esta função bloqueia
até que o thread especificado por tid termine*/