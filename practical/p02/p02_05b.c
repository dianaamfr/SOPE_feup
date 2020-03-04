// PROGRAMA p5b.c

 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <unistd.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>


int main(void)
{
  int fd;
  char *text1="CCCCC";
  char *text2="DDDDD";

  //O_APPEND => added to add new text at end of file
  if((fd = open("f1.txt", O_WRONLY|O_SYNC|O_APPEND,0600))==-1){
    perror("f1.txt");
    exit(2);
  }

  getchar(); //Allow user to control the order of the operations

  if(write(fd,text1,5) == -1){
    perror("Error writing to file\n");
    close(fd);
    exit(1);
  }

  getchar();

  if(write(fd,text2,5) == -1){
    perror("Error writing to file\n");
    close(fd);
    exit(1);
  }

  close(fd);

  return 0;
}

