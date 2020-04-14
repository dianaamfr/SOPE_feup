//======================================================================
// THREADS - examples
// t02.c
// What may happen if the main thread is the first one to end ... :-(
//----------------------------------------------------------------------
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void *thr_func(void *arg)
{
 sleep(3);
 printf("Hello from auxiliar thread\n"); return NULL;// não chega a ser impressa
}
int main(void)
{
 pthread_t tid;
 printf("Hello from main thread\n");
 pthread_create(&tid, NULL, thr_func, NULL);
 return 0;
} 

/*Se main() terminar
porque executou exit(), _exit(), return ou atingiu a última instrução
os threads por si criados também terminarão automaticamente.*/