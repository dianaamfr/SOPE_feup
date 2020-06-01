// POSIX shared memory & semaphore
// Program that writes a digit sequence in shared memory and waits for a reader to read it

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>

#define SHM_SIZE 10

// names should begin with '/'
char SEM_NAME1[] = "/sem1";
char SEM_NAME2[] = "/sem2";
char SHM_NAME[] = "/shm";

int main(){
   int shmfd;
   char *shm;
   sem_t *sem1, *sem2;
   
   // Create shared memory region
   if((shmfd = shm_open(SHM_NAME, O_CREAT|O_RDWR, 0600)) < 0){
      perror("WRITER failure in shm_opne()");
      exit(1);
   }

   // Define the size of the shared memory
   if(ftruncate(shmfd, SHM_SIZE) < 0){
      perror("WRITER failure in ftruncate()");
      exit(2);
   }

   // Attach this region to virtual memory
   if((shm = (char*)mmap(0,SHM_SIZE,PROT_READ|PROT_WRITE, MAP_SHARED, shmfd, 0)) == MAP_FAILED){
      perror("WRITER failure in mmap()");
      exit(3);
   }

   // Create and initialize semaphores
   if((sem1 = sem_open(SEM_NAME1, O_CREAT, 0600, 0)) == SEM_FAILED){
      perror("WRITER failure in sem_open(sem1)");
      exit(4);
   }
   if(sem2 = sem_open(SEM_NAME2, O_CREAT, 0600, 0)) == SEM_FAILED){
      perror("WRITER failure in sem_open(sem2)");
      exit(5);
   }

   // Write into shared memory region
   char * s = shm;
   int n, sum = 0;
   for(int i = 0; i < SHM_SIZE - 1; i++){ // Digits will have one less space - used to terminate de string with '\0'
      n = i % 10; // Write a sequence of digits (each digit is in the range 0 to 9)
      sum += n;
      // s works like an iterator that goes through all the positions of the shared memory region
      // Here, in the address of s we store the digit and, after that, update s to next position (note the postfix increment)
      *s++ = (char)('0' + n); // A char in C is already a number (the character's ASCII code). To convert a digit to the corresponding character, simply add '0'
   }
   *s = (char)0; // To end the string
   printf("sum = %d\n",sum);

   sem_post(sem1); // Allows the reader to read

   sem_wait(sem2); // Blocks until the reader ends reading and does the sem_post() on sem2

   // Close and remove shared memory region and semaphores
   sem_close(sem1);
   sem_close(sem2);
   sem_unlink(SEM_NAME1);
   sem_unlink(SEM_NAME2);

   if(munmap(shm, SHM_SIZE) < 0){
      perror("WRITER failure in munmap()");
      exit(6);
   }
   
   if(shm_unlink(SHM_NAME) < 0){
      perror("WRITER failure in shm_unlink()");
      exit(7);
   }

   exit(0);
}