#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#define MAX_NAME_SIZE   50
#define MAX_GRADE_SIZE  2
#define MAX_STUDENTS    20

struct student{
   int grade;
   char name[MAX_NAME_SIZE+1];
};

int main(int argc, char *argv[]){
   int fd;
   struct student s;
   char grade[MAX_GRADE_SIZE+1];

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

      memset(s.name,0,sizeof(s.name));
      memset(grade,0,sizeof(grade));

      printf("Student %d: ",i+1);
      fgets(s.name,MAX_NAME_SIZE+1,stdin);

      if (s.name[strlen(s.name)-1] == '\n')
         s.name[strlen(s.name)-1] = '\0';
      else getchar();

      if(s.name[0] == '\0') break;

      printf("Grade %d: ", i+1);
      fgets(grade,MAX_GRADE_SIZE+1,stdin);

      if(grade[strlen(grade)-1] == '\n'){
         grade[strlen(grade)-1] = '\0';
      }else getchar();

      s.grade = atoi(grade);

      if(write(fd, &s, sizeof(struct student))!=sizeof(struct student)){
         perror(argv[1]);
         close(fd);
         exit(3);
      }
      i++;
   }

   close(fd);

   return 0;
}