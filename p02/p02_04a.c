#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#define MAX_NAME_SIZE   30
#define MAX_GRADE_SIZE  2
#define MAX_STUDENTS    20

int main(int argc, char *argv[]){
   char grade[MAX_GRADE_SIZE+1];
   char name[MAX_NAME_SIZE+1]= "empty";
   int fd;

   if(argc != 2){
      printf("Usage: %s <destination>\n",argv[0]);
      exit(1);
   }

   if((fd = open(argv[1],O_CREAT|O_WRONLY|O_APPEND, 0644)) == -1 ){
      perror(argv[1]);
      exit(2);
   }

   int i=0;
   printf("Press ENTER to stop reading!\n");

   while(i < MAX_STUDENTS){

      memset(name,0,sizeof(name));
      memset(grade,0,sizeof(grade));

      printf("Student %d: ",i+1);
      fgets(name,MAX_NAME_SIZE+1,stdin);

      if (name[strlen(name)-1] == '\n')
         name[strlen(name)-1] = '\0';
      else getchar();

      if(name[0] == '\0') break;

      printf("Grade %d: ", i+1);
      fgets(grade,MAX_GRADE_SIZE+1,stdin);

      if(grade[strlen(grade)-1] == '\n'){
         grade[strlen(grade)-1] = '\0';
      }else getchar();

      if(write(fd, name, strlen(name))!=strlen(name)){
         perror(argv[1]);
         close(fd);
         exit(3);
      }
      if(write(fd, " ", 1)!=1){
         perror(argv[1]);
         close(fd);
         exit(3);
      }
      if(write(fd, grade, strlen(grade))!=strlen(grade)){
         perror(argv[1]);
         close(fd);
         exit(3);
      }

       if(write(fd, "\n", 1)!=1){
         perror(argv[1]);
         close(fd);
         exit(3);
      }

      i++;
   }

   close(fd);

   return 0;
}