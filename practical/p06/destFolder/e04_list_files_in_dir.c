/*List regular files in directory*/
/*uses: listdir dirname*/

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
   /*!!!!*/
   DIR *dir;
   int line;
   /*!!!!*/
   struct dirent *dentry; //tp fill with info about a directory entry 
   /*!!!!*/
   struct stat stat_entry; // to fill with information about a file

   //Write usage message on the screen if the wrong number of arguments is given
   if(argc != 2){
      printf("Usage: %s <dir_path>\n",argv[0]);
      return 1; //operation no permitted
   }

   /*!!!!*/
   // dir points to the directory or is NULL, in which case an error must be thrown 
   if((dir = opendir(argv[1])) == NULL){
      perror(argv[1]);
      return 2; // no such directory error
   }

   /*!!!!*/
   //change process's current directory to the onde specified in the argument
   chdir(argv[1]);

   printf("Regular files in directory '%s'\n",argv[1]);
   line = 1;
   //while new entries are succesfully read from the directory
   while((dentry = readdir(dir))!= NULL){/*!!!!*/
      //get information and attributtes about an entry
      stat(dentry->d_name, &stat_entry);/*!!!!*/

      //if it is a regular file
      if(S_ISREG(stat_entry.st_mode)){/*!!!!*/
         //print it's name, byte size and links count
         //text justify left(-) with widths 20, 12 and 3
         printf("%-25s%12d%3d\n",dentry->d_name,(int)stat_entry.st_size,(int)stat_entry.st_nlink);
         if(line++ % 20 == 0){ //imprime 20 de cada vez
            printf("Press <enter> to continue");
            getchar();
         }
      }
   }
}