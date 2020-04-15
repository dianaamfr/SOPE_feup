
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct numbers {
   int n1;
   int n2;
};

void *sum(void *arg)
{
   int * nums = (int *) arg;
   void *ret = malloc(30*sizeof(char)); 
   char res[30];

   sprintf(res, "Sum: %d",nums[0] + nums[1]); 

   memcpy((char *)ret, &res, 30);
   return ret;
}

void *sub(void *arg)
{
   int * nums = (int *) arg;
   void *ret = malloc(30*sizeof(char)); 
   char res[30];

   sprintf(res, "Subtraction: %d",nums[0] - nums[1]); 

   memcpy((char *)ret, &res, 30);
   return ret;
}

void *prod(void *arg)
{
   int * nums = (int *) arg;
   void *ret = malloc(30*sizeof(char)); 
   char res[30];

   sprintf(res, "Product: %d",nums[0] * nums[1]); 
   
   memcpy((char *)ret, &res, 30);
   return ret;
}

void *quoc(void *arg)
{
   int * nums = (int *) arg;
   void *ret = malloc(30*sizeof(char)); 
   char res[30];

   sprintf(res,"Quocient: %f",nums[0] / (float)nums[1]); 
   
   memcpy((char *)ret, &res, 30);
   return ret;
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

   void * r;
   for(int i = 0; i<4; i++){
      pthread_join(threads[i],&r);
      printf("Thread %d: %s\n",i,(char *)r);
   }


   free(nums);
   free(r);
   pthread_exit(0);
}