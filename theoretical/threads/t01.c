//======================================================================
// THREADS - examples
// t01.c
// A program that launches 2 threads and waits for them to end
// Illustrating thread execution interleaving
//----------------------------------------------------------------------
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_CHARS 10000
void *thr_func(void *arg)
{
 int i;
 fprintf(stderr, "Starting thread %s\n", (char *) arg); 
 
 for (i = 0; i < NUM_CHARS; i++)
   write(STDOUT_FILENO,(char *) arg,1);
 return NULL;
}
int main(void)
{
 pthread_t tid1, tid2;
 printf("Hello from main thread\n");
 pthread_create(&tid1, NULL, thr_func, "A");
 pthread_create(&tid2, NULL, thr_func, "B");
 pthread_join(tid1,NULL);
 pthread_join(tid2,NULL);
 return 0;
} 