#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define STDERR 2

int n = 50000;

void * thrfunc(void * arg)
{
    int i = 0;
    fprintf(stderr, "Starting thread %s\n", (char *) arg);
    while (n > 0) {
        n--;
        i++;
        write(STDERR,arg,1);
    }

    void * ret = malloc(sizeof(int));
    *(int *)ret = i;
    return ret;
}

int main()
{
    pthread_t ta, tb;
    void * a, * b;

    pthread_create(&ta, NULL, thrfunc, "1");
    pthread_create(&tb, NULL, thrfunc, "2");
    pthread_join(ta, &a);
    pthread_join(tb, &b);

    fprintf(stderr, "\nThread 1: %d\n", *(int *) a);
    fprintf(stderr, "Thread 2: %d\n", *(int *) b);
    fprintf(stderr, "Total: %d times!\n", *(int *)a + *(int *)b); 

    return 0;
} 

/*
   o problema que pode ocorrer: Ambas alteram a mesma variável global pelo que não é garantido que o mesmo valor seja alterado pelas duas threads em simultâneo.

*/