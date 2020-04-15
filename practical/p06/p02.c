// PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define STDERR 2
#define NUMITER 10000

int n = 50000;

void * thrfunc(void * arg)
{
   int i;
   void *ret; 

   fprintf(stderr, "Starting thread %s\n", (char *) arg);

   for (i = 1; i < n; i++) 
      n--;
   
   ret = malloc(sizeof(int));
   *(int *)ret = i;
   return ret;
}

int main()
{   

   pthread_t ta, tb;
   void * a, *b;

   pthread_create(&ta, NULL, thrfunc,"1");
   pthread_create(&tb, NULL, thrfunc,"2");
   pthread_join(ta, &a);
   pthread_join(tb, &b);
   printf("Thread 1 printed %d times!\n", *(int *)a); 
   printf("Thread 2 printed %d times!\n", *(int *)b); 
   printf("Total: %d times!\n", *(int *)a + *(int *)b); 

   free(a);
   free(b);
   return 0;
} 

/*
   o problema que pode ocorrer: Ambas alteram a mesma variável global pelo que não é garantido que o mesmo valor seja alterado pelas duas threads em simultâneo.

*/