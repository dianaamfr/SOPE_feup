// PROGRAMA p03.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

void *PrintHello(void *threadnum)
{
   printf("Hello from thread no. %d!\n", *(int *) threadnum);
   pthread_exit(NULL);
}

int main()
{
   pthread_t threads[NUM_THREADS];
   int t;
   for(t=0; t< NUM_THREADS; t++){
   printf("Creating thread %d\n", t);
   pthread_create(&threads[t], NULL, PrintHello, (void *)&t);
   pthread_join(threads[t],NULL);
   }
 pthread_exit(0);
}


/*
a) Utilizando o código fornecido:

int main()
{
 pthread_t threads[NUM_THREADS];
 int t;
 for(t=0; t< NUM_THREADS; t++){
 printf("Creating thread %d\n", t);
 pthread_create(&threads[t], NULL, PrintHello, (void *)&t);
 }
 pthread_exit(0);
}

Verifica-se que por vezes algumas threads quando executadas já recebem o valor que deveria ser enviado à thread seguinte. Isto deve-se ao facto de
as threads receberem sempre o mesmo endereço de memória, sendo este atualizado logo de seguida e produzindo resultados insesperados.

b) Uma opção é usar o pthread_join(tid,NULL);

Outra opção:

void *PrintHello(void *threadnum)
{
 printf("Hello from thread no. %d!\n", *(int *) threadnum);
 free(threadnum);
 pthread_exit(NULL);
}

int main()
{
   pthread_t threads[NUM_THREADS];
   int t;
   int *thrArg;
   
   for(t=0; t< NUM_THREADS; t++){
      thrArg = (int *) malloc(sizeof(t));
      *thrArg = t;
      printf("Creating thread %d\n", t);
      pthread_create(&threads[t], NULL, PrintHello, thrArg);
   }
   pthread_exit(0);
}


c) explicação do prof: "pthread_exit mata uma thread (a calling thread) enquanto que o exit() termina o programa normalmente. 
O main do vosso programa é também uma thread. O pthread_exit termina apenas assim apenas a thread respectiva e as outras continuam."

Portanto, substituindo pthread_exit por exit() podemos correr o risco de terminar o programa sem algumas threads chegarem a executar.

*/