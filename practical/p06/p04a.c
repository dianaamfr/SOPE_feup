#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_ITER 20
#define N 10

void *thrFunc(void *arg)
{  
   void *ret; 

   sleep(1); 
   printf("In function \nthread tid = %lu\n", pthread_self());
   
   ret = malloc(sizeof(int));
   *(int *)ret = *(int *) arg;
   return ret;
}

int main(void)
{
   pthread_t tid;
   int t=1;
   
   for(int i = 0; i < N; i++){
      pthread_create(&tid, NULL, thrFunc, (void *)&t); 
      pthread_join(tid,NULL);
      t++;
   }
   
    pthread_exit(0);
} 

/*Nota do prof: Relembro que se fizerem thread_create e thread_join no mesmo "loop", as vossas threads vão 
ter um comportamento "sequencial" logo todas devem/irão ter o mesmo TID*/