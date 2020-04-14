//======================================================================
// THREADS - examples
// t05.c
// Passing info through thread arguments and return values
//----------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_func(void *arg)
{
 void *ret;
 int value;
 value = *(int *) arg;
 printf("Aux thread: %d\n",value);
 value++;
 ret = malloc(sizeof(int));
 *(int *)ret = value; 
 return ret;
}

int main(void)
{
 pthread_t tid;
 int k = 10;
 void *r;
 pthread_create(&tid, NULL, thr_func, &k);
 pthread_join(tid, &r);
 printf("Main thread: %d\n", *(int *)r);
 free(r);
 return 0;
} 