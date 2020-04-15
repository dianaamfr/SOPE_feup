
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct numbers {
   int n1;
   int n2;
};

void *sum(void *arg)
{
   int * nums = (int *) arg;

   printf("Sum: %d\n",nums[0] + nums[1]); 
   pthread_exit(NULL);
}

void *sub(void *arg)
{
   int * nums = (int *) arg;

   printf("Subtraction: %d\n",nums[0] - nums[1]); 
   pthread_exit(NULL);
}

void *prod(void *arg)
{
   int * nums = (int *) arg;

   printf("Product: %d\n",nums[0] * nums[1]); 
   pthread_exit(NULL);
}

void *quoc(void *arg)
{
   int * nums = (int *) arg;

   printf("Quocient: %f\n",nums[0] / (float)nums[1]); 
   pthread_exit(NULL);
}

int main(){
   int * nums= (int *) malloc(sizeof(int)*2);
   pthread_t threads[4];

   printf("Number 1: ");
   scanf("%d",&nums[0]);
   printf("Number 2: ");
   scanf("%d",&nums[1]);

   pthread_create(&threads[0], NULL, sum, nums);
   pthread_create(&threads[1], NULL, sub, nums);
   pthread_create(&threads[2], NULL, prod, nums);
   pthread_create(&threads[3], NULL, quoc, nums);

   for(int i = 0; i<4; i++)
      pthread_join(threads[i],NULL);

   free(nums);

   pthread_exit(0);
}