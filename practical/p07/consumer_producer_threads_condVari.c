// PRODUCER-CONSUMER PROBLEM
// PRODUCERS AND CONSUMERS ARE THREADS OF A SINGLE PROCESS
// SYNCHRONIZATION USING CONDITION VARIABLES

//======================================================================
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
//======================================================================
#define BUFSIZE 8
#define NUMITEMS 100
//======================================================================
int buffer[BUFSIZE];
int bufin = 0;
int bufout = 0;
int items = 0;
int slots = 0;
int sum = 0;
//======================================================================
pthread_mutex_t buffer_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t slots_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t items_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t slots_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t items_lock = PTHREAD_MUTEX_INITIALIZER;
//======================================================================
void put_item(int item)
{
 pthread_mutex_lock(&buffer_lock);
 buffer[bufin] = item;
 bufin = (bufin + 1) % BUFSIZE;
 pthread_mutex_unlock(&buffer_lock);
 return;
}
//======================================================================
void get_item(int *itemp)
{
 pthread_mutex_lock(&buffer_lock);
 *itemp = buffer[bufout];
 bufout = (bufout + 1) % BUFSIZE;
 pthread_mutex_unlock(&buffer_lock);
 return;
}
//======================================================================
void *producer(void * arg)
{
 int i;
 for (i = 1; i <= NUMITEMS; i++)
 {
 /* acquire right to a slot */
 pthread_mutex_lock(&slots_lock);
 printf("Producer: available slots = %d\n",slots);
 while (!(slots > 0))
 pthread_cond_wait (&slots_cond, &slots_lock); 
 slots--;
 pthread_mutex_unlock(&slots_lock);
 put_item(i);
 printf("Producer: produced item %3d\n",i);
 /* release right to an item */
 pthread_mutex_lock(&items_lock);
 items++;
 pthread_cond_signal(&items_cond);
 pthread_mutex_unlock(&items_lock);
 }
 pthread_exit(NULL);
}
//======================================================================
void *consumer(void *arg)
{
 int myitem;
 int i;
 for (i = 1; i <= NUMITEMS; i++)
 {
 pthread_mutex_lock(&items_lock);
 printf("Consumer: available items = %d\n",items);
 while(!(items > 0))
 pthread_cond_wait(&items_cond, &items_lock);
 items--;
 pthread_mutex_unlock(&items_lock);
 get_item(&myitem);
 printf("Consumer: consumed item %3d\n",myitem);
 sum += myitem;
 pthread_mutex_lock(&slots_lock);
 slots++;
 pthread_cond_signal(&slots_cond);
 pthread_mutex_unlock(&slots_lock);
 }
 pthread_exit(NULL);
}
//======================================================================
int main(void)
{
 pthread_t prodtid, constid;
 int i, total;
 slots = BUFSIZE;
 total = 0;
 for (i = 1; i <=NUMITEMS; i++)
 total += i;
 printf("The checksum is %d\n", total);
 if (pthread_create(&constid, NULL, consumer, NULL))
 {
 perror("Could not create consumer");
 exit(EXIT_FAILURE);
 }
 if (pthread_create(&prodtid, NULL, producer, NULL))
 {
 perror("Could not create producer");
 exit(EXIT_FAILURE);
 } 
 pthread_join(prodtid, NULL);
 pthread_join(constid, NULL);
 printf("The threads produced the sum %d\n", sum);
 exit(EXIT_SUCCESS);//EXIT_SUCCESS e EXIT_FAILURE <- stdlib.h
} 