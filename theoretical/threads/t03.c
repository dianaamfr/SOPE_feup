//======================================================================
// THREADS - examples
// t03.c
// - A child thread can continue running after the main thread end !!!
// - Passing info between threads using global variables
//----------------------------------------------------------------------
#include <stdio.h>
#include <pthread.h>
int global;
void *thr_func(void *arg)
{
 printf("Aux thread: %d\n", global); return NULL;
}
int main(void)
{
 pthread_t tid;
 global = 20;
 printf("Main thread: %d\n", global);
 pthread_create(&tid, NULL, thr_func, NULL);
 pthread_exit(NULL);
} 

/* Desta forma, o thread auxiliar
pode continuar a executar
mesmo depois de main() terminar.

pthread_exit

Se main() terminar com a chamada pthread_exit()
os outros threads continuarão em execução;
as variáveis globais não serão destruídas e
os ficheiros abertos não serão fechados.
*/