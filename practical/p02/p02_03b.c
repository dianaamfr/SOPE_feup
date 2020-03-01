#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_CHARS_TO_READ 700

int main(int argc, char *argv[]){
   int sourceFd,destFd;
   int bytesRead, bytesWritten;
   char buffer[MAX_CHARS_TO_READ+1];
   
   if(argc != 2 && argc != 3){
      printf("\nUsage: %s <source>  OR %s <source> <destination>\n",argv[0],argv[0]);
      return 1;
   }

   if((sourceFd = open(argv[1],O_RDONLY))== -1){
      perror(argv[1]);
      return 2;
   }

   if(argc == 3){
      if((destFd = open(argv[2],O_WRONLY,S_IWUSR|S_IRUSR |S_IROTH|S_IRGRP)) == -1){
         perror(argv[2]);
         close(sourceFd);
         return 2;
      }
      dup2(STDOUT_FILENO,sourceFd);
   }

   //try to read the max number of chars defined until end of
   while((bytesRead = read(sourceFd,buffer,MAX_CHARS_TO_READ+1)) > 0){
      if((bytesWritten = write(STDERR_FILENO,buffer,bytesRead)) <= 0 || bytesRead != bytesWritten){ 
         perror(argv[2]);
         close(sourceFd);
         return 4;
      }
      close(sourceFd);
      return 0;
   }

   return 0;
}