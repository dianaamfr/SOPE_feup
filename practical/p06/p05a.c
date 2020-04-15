
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct numbers {
   int n1;
   int n2;
};

void *sum(void *arg)
{
   struct numbers nums = *(struct numbers *) arg;

   printf("Sum: %d\n",nums.n1 + nums.n2); 
   pthread_exit(NULL);
}

void *sub(void *arg)
{
   struct numbers nums = *(struct numbers *) arg;

   printf("Subtraction: %d\n",nums.n1 - nums.n2); 
   pthread_exit(NULL);
}

void *prod(void *arg)
{
   struct numbers nums = *(struct numbers *) arg;

   printf("Product: %d\n",nums.n1 * nums.n2); 
   pthread_exit(NULL);
}

void *quoc(void *arg)
{
   struct numbers nums = *(struct numbers *) arg;

   printf("Quocient: %f\n",nums.n1 / (float)nums.n2); 
   pthread_exit(NULL);
}

int main(){
   struct numbers * nums = (struct numbers *) malloc(sizeof(nums));
   pthread_t threads[4];

   printf("Number 1: ");
   scanf("%d",&nums->n1);
   printf("Number 2: ");
   scanf("%d",&nums->n2);

   pthread_create(&threads[0], NULL, sum, nums);
   pthread_create(&threads[1], NULL, sub, nums);
   pthread_create(&threads[2], NULL, prod, nums);
   pthread_create(&threads[3], NULL, quoc, nums);

   for(int i = 0; i<4; i++)
      pthread_join(threads[i],NULL);
   
   free(nums);

   pthread_exit(0);
}