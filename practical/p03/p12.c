#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h> 

#define BUFFER_SIZE 2500
#define DIR_NAME_SIZE 50

int main(int argc, char * argv[]){

   DIR *srcDir, *destDir;
   struct dirent *dirEntry;
   struct stat statEntry;
   pid_t pid, childPid;
   int srcFd, destFd, nr, nw;
   int status;
   unsigned char buffer[BUFFER_SIZE];
   char srcDirName[DIR_NAME_SIZE];
   char destDirName[DIR_NAME_SIZE];
   
   if(argc != 3){
      printf("Usage: %s <source dir> <dest dir>\n",argv[0]);
      return 1;
   }
   if((srcDir = opendir(argv[1])) == NULL){
      perror(argv[1]);
      return 2;
   }
   if((destDir = opendir(argv[1])) == NULL){
      closedir(srcDir);
      perror(argv[2]);
      return 3;
   }


   if(chdir(argv[1]) == -1){
      perror(argv[1]); 
      return 6;
   }
   memcpy(srcDirName,"../",3);
   memcpy(&srcDirName[3],argv[1],DIR_NAME_SIZE-3);

   memcpy(destDirName,"../",3);
   memcpy(&destDirName[3],argv[2],DIR_NAME_SIZE-3);

   printf("Parent pid = %d\n", getpid());

   while((dirEntry = readdir(srcDir)) != NULL){
      stat(dirEntry->d_name,&statEntry);
      if(S_ISREG(statEntry.st_mode)){

         pid = fork();

         if(pid > 0){ /*parent*/
            childPid = wait(&status);
            printf("In parent (%d) -> File copied (child pid = %d)\n",getpid(),childPid);
            close(srcFd);
            close(destFd);
            
            if(chdir(srcDirName) == -1){
               perror(srcDirName); 
               return 6;
            }
         }
          else{ /*child*/
            printf("Child %d-> copying file\n",getpid());
            srcFd = open(dirEntry->d_name,O_RDONLY);
            if(srcFd == -1){
               perror(dirEntry->d_name); 
               return 4; 
            }

            if(chdir(destDirName) == -1){
               perror(destDirName); 
               return 7;
            }
            destFd = open(dirEntry->d_name, O_WRONLY|O_CREAT|O_EXCL,0644);
            if(destFd == -1){
               perror(dirEntry->d_name); 
               close(srcFd); 
               return 5;
            }

            while((nr = read(srcFd,buffer,BUFFER_SIZE))>0){
               if((nw = write(destFd,buffer,nr)) <= 0 || nw != nr){ 
                  perror(dirEntry->d_name);
                  close(srcFd);
                  close(destFd);
                  return 4;
               }
               close(srcFd);
               close(destFd);
               return 0;
            }

         }
      }
   }


   return 0;
}