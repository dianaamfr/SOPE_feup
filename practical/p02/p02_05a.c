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
  char *text1="AAAAA";
  char *text2="BBBBB";

  //O_EXCL => with O_CREAT ensures that this call creates the file = > removed to allow 5b to execute before 5a
  //O_TRUNC =>If  the file already exists and is a regular file and the access
              //mode allows writing (i.e., is O_RDWR or  O_WRONLY)  it  will  be
              //truncated to length 0

  if((fd = open("f1.txt",O_CREAT|O_TRUNC|O_WRONLY|O_SYNC,0600)) == -1){
    perror("f1.txt");
    exit(2);
  }

  getchar(); //Allow user to control the order of the operations

  if(write(fd,text1,5) == -1){
    perror("Error writing to file\n");
    close(fd);
    exit(1);
  }

  getchar(); //Allow user to control the order of the operations

  if(write(fd,text2,5) == -1){
    perror("Error writing to file\n");
    close(fd);
    exit(1);
  }

  close(fd);
  return 0;
}

