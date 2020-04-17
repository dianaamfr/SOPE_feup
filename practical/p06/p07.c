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
#include <pthread.h>

#define FAIL 1
#define OK 0

#define MAX_PATH 100
#define FILE_NAME_SIZE 50
#define DIR_NAME_SIZE 50

#define BUFFER_SIZE 2500

#define NUM_THREADS 100

struct dirs{
   char * srcDirName;
   char * destDirName;
   char * filename;
};

void * copyFile(void * arg)
{  
   struct dirs * d = (struct dirs *) arg;
   int srcFd, destFd, nr, nw;
   char buffer[BUFFER_SIZE];

   char * origFile = (char*)malloc(sizeof(char)* MAX_PATH);
   char * destFile = (char*)malloc(sizeof(char)* MAX_PATH);

   if(snprintf(origFile,MAX_PATH, "%s/%s", d->srcDirName, d->filename) < 0) 
      exit(FAIL);
   
   if(snprintf(destFile,MAX_PATH, "%s/%s", d->destDirName, d->filename) < 0) 
      exit(FAIL);

   free(d->srcDirName);
   free(d->destDirName);

   srcFd = open(origFile,O_RDONLY);
   if(srcFd == -1){
      perror(origFile); 
      exit(FAIL);
   }

   destFd = open(destFile,O_WRONLY|O_CREAT,0644);
   if(destFd == -1){
      perror(destFile); 
      exit(FAIL);
   }

   while((nr = read(srcFd,buffer,BUFFER_SIZE)) > 0){
      if((nw = write(destFd,buffer,nr)) <= 0 || nw != nr){ 
         perror(d->filename);
         close(srcFd);
         close(destFd);
         exit(FAIL);
      }
   }

   close(srcFd);
   close(destFd);

   free(d->filename);
   free(d);

   free(origFile);
   free(destFile);

   return NULL;
}

int main(int argc, char * argv[]){

   DIR *srcDir, *destDir;
   struct dirent *dirEntry;
   struct stat statEntry;
   
   if(argc != 3){
      printf("Usage: %s <source dir> <dest dir>\n",argv[0]);
      exit(FAIL);
   }
   if((srcDir = opendir(argv[1])) == NULL){
      perror(argv[1]);
      exit(FAIL);
   }
   if((destDir = opendir(argv[2])) == NULL){
      closedir(srcDir);
      perror(argv[2]);
      exit(FAIL);
   }

   pthread_t threads[NUM_THREADS];
   int t = 0;

   while((dirEntry = readdir(srcDir)) != NULL){

      char * origFile = (char*)malloc(sizeof(char)* MAX_PATH);

      if(snprintf(origFile,MAX_PATH, "%s/%s", argv[1], dirEntry->d_name) < 0) 
         exit(FAIL);
      
      if(lstat(origFile,&statEntry) != OK){
         fprintf(stderr,"Lstat error in %s\n",dirEntry->d_name);
         exit(FAIL);
      }

      free(origFile);

      if(S_ISREG(statEntry.st_mode)){

         struct dirs * d = (struct dirs *)malloc(sizeof(struct dirs));
         d->destDirName = (char*) malloc(sizeof(char)*DIR_NAME_SIZE);
         d->srcDirName = (char*) malloc(sizeof(char)*DIR_NAME_SIZE);
         d->filename = (char*) malloc(sizeof(char)*FILE_NAME_SIZE);

         strcpy(d->srcDirName,argv[1]);
         strcpy(d->destDirName,argv[2]);
         strcpy(d->filename,dirEntry->d_name);

         pthread_create(&threads[t], NULL,copyFile,d);

         t++;
      }
   }

   closedir(srcDir);
   closedir(destDir);

   pthread_exit(OK);
}