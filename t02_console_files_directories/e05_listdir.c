#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[]){
   DIR *dirp;
   struct dirent *direntp;
   struct stat stat_buf;
   char *str;
   char name[260];

   if(argc != 2){
      //write output to error streamq
      fprintf(stderr,"Usage: %s <dir_name>\n",argv[0]);
      exit(1);
   }

   if((dirp=opendir(argv[1])) == NULL){
      perror(argv[1]);
      exit(2);
   }

   while((direntp = readdir(dirp))!= NULL){
      //store directory name in name buffer
      sprintf(name,"%s/%s",argv[1],direntp->d_name);
      //retrieve information about the file pointed to by
      //pathname and if that pathname is a symbolic link return
      //info about the link itself, not the file it refers to
      if(lstat(name, &stat_buf) == -1){
         perror("lstat ERROR");
         exit(3);
      }
      printf("%10d - ",(int) stat_buf.st_ino); 
      if(S_ISREG(stat_buf.st_mode))
         str = "regular";
      else if(S_ISDIR(stat_buf.st_mode))
         str = "directory";
      else
         str = "other";
      printf("%-25s - %s\n",direntp->d_name,str);
   }
   closedir(dirp);
   exit(0);
}