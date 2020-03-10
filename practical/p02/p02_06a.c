// PROGRAMA p6a.c ( referido na alínea a) )
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX_PATH_SIZE 300
int main(int argc, char *argv[])
{
   DIR *dirp;
   struct dirent *direntp;
   struct stat stat_buf;
   char *str;
   char name[MAX_PATH_SIZE]; 
   if (argc != 2)
   {
      fprintf( stderr, "Usage: %s dir_name\n", argv[0]);
      exit(1);
   }
   if ((dirp = opendir( argv[1])) == NULL)
   {
      perror(argv[1]);
      exit(2);
   }
   while ((direntp = readdir(dirp)) != NULL)
   {
      sprintf(name,"%s/%s",argv[1],direntp->d_name); // <----- NOTAR //guarda o path+nome
      // alternativa a chdir(); ex: anterior 
      /*lstat() is identical to stat(), except that if pathname is  a  symbolic
       link,  then  it returns information about the link itself, not the file
       that it refers to.*/
      if( lstat(name, &stat_buf) == -1){
         perror("lstat ERROR");
         exit(3);
      }

      if (S_ISREG(stat_buf.st_mode)) str = "regular";
      else if (S_ISDIR(stat_buf.st_mode)) str = "directory";
      else str = "other";

      printf("%-25s%12s%12d  %3d\n", direntp->d_name,str,(int)stat_buf.st_size,(int)stat_buf.st_ino);
      
   }
   closedir(dirp);
   exit(0);
} 