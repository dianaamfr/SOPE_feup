#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

sem_t sem1;
sem_t sem2;
sem_t sem3;

void * thrFunc1(void * arg){
   printf("I am P1\n");
   sleep(1);

   printf("A\n");
   sem_post(&sem1);
   sem_post(&sem1);
   printf("P1: Waiting for P2 to reach B\n");
   sem_wait(&sem2);
   printf("P1: Waiting for P3 to reach C\n");
   sem_wait(&sem3);
   printf("P1: Waited for P2 to reach B and P3 to reach C\n");
   return NULL;
}

void * thrFunc2(void * arg){
   printf("I am P2\n");
   sleep(2);

   printf("B\n");
   sem_post(&sem2);
   sem_post(&sem2);
   printf("P2: Waiting for P1 to reach A\n");
   sem_wait(&sem1);
   printf("P2: Waiting for P3 to reach C\n");
   sem_wait(&sem3);
   printf("P2: Waited for P1 to reach A and P3 to reach C\n");
   return NULL;
}

void * thrFunc3(void * arg){
   printf("I am P3\n");
   sleep(3);

   printf("C\n");
   sem_post(&sem3);
   sem_post(&sem3);
   printf("P3: Waiting for P1 to reach A\n");
   sem_wait(&sem1);
   printf("P3: Waiting for P2 to reach B\n");
   sem_wait(&sem2);
   printf("P3: Waited for P1 to reach A and P2 to reach B");
   return NULL;
}

int main(void){
   sem_init(&sem1, 0, 0);
   sem_init(&sem2, 0, 0);
   sem_init(&sem3, 0, 0);

   pthread_t t1, t2, t3;
   pthread_create(&t1,NULL,thrFunc1,NULL); 
   pthread_create(&t2,NULL,thrFunc2,NULL); 
   pthread_create(&t3,NULL,thrFunc3,NULL); 

   pthread_exit(0);
}