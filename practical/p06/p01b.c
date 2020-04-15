// PROGRAMA p01.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define STDERR 2
#define NUMITER 10000

void * thrfunc(void * arg)
{
   int i;

   fprintf(stderr, "Starting thread %s\n", (char *) arg);

   for (i = 1; i <= NUMITER; i++) 
      write(STDERR,arg,1);
   return NULL;
}

int main()
{   
   char one = '1';
   char two = '2';
   

   pthread_t ta, tb;
   pthread_create(&ta, NULL, thrfunc,(void*)&one);
   pthread_create(&tb, NULL, thrfunc,(void*)&two);
   pthread_join(ta, NULL);
   pthread_join(tb, NULL);

   return 0;
} 

/*
caso seja usada a mesma variável para guardar o parâmetro de cada uma das threads pode acontecer que a primeira nunca 
chega a ser executada com o parâmetro desejado - recebe o mesmo valor.

int *one = (int *) malloc(sizeof(int));
   int *two = (int *) malloc(sizeof(int));
   *one = 1;
   *two = 2;

would generate a strange output because in the thread function the argument is printed by converting it to char*
*/