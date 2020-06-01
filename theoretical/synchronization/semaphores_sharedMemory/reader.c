// POSIX shared memory & semaphore
// Program that reads a digit sequence from shared memory and signals the READER so he can remove the shared memory region


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
   
   // Open shared memory region
   if((shmfd = shm_open(SHM_NAME, O_RDWR, 0600)) < 0){
      perror("READER failure in shm_open()");
      exit(1);
   }

   // Attach this region to virtual memory
   if((shm = (char*)mmap(0,SHM_SIZE,PROT_READ|PROT_WRITE, MAP_SHARED, shmfd, 0)) == MAP_FAILED){
      perror("READER failure in mmap()");
      exit(2);
   }

   // Create and initialize semaphores
   if((sem1 = sem_open(SEM_NAME1, 0, 0600, 0)) == SEM_FAILED){
      perror("READER failure in sem_open(sem1)");
      exit(3);
   }
   if((sem2 = sem_open(SEM_NAME2, 0, 0600, 0)) == SEM_FAILED){
      perror("READER failure in sem_open(sem2)");
      exit(4);
   }

   // Wait for writer to stop writing 
   sem_wait(sem1);

   // Read the message
   char * s, ch;
   int sum = 0;
   for(s = shm; *s != 0; s++){ 
      ch = *s;
      putchar(ch);
      sum += ch - '0';
   }
   printf("\nsum = %d\n",sum);

   sem_post(sem2);

   // Close and remove shared memory region and semaphores
   sem_close(sem1);
   sem_close(sem2);

   if(munmap(shm, SHM_SIZE) < 0){
      perror("READER failure in munmap()");
      exit(5);
   }

   exit(0);
}