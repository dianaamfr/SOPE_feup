/*copy file*/

#include <stdio.h> //printf()
#include <unistd.h>
#include <fcntl.h> //open()
#include <errno.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[]){
   int fd1,fd2,nr,nw;
   unsigned char buffer[BUFFER_SIZE];

   //check for correct number of attributes and if the wrong number is 
   //passed print usage message and end program
   if(argc != 3){
      printf("Usage: %s <source> <destination>\n",argv[0]);
      return 1; //operation not permitted
   }

   //if 3 arguments were passed
   
   //open source file for reading purposes (O_RDONLY)
   fd1 = open(argv[1],O_RDONLY);
   //if error occurs opening source file
   if(fd1 == -1){
      perror(argv[1]);//print a system error message with name of file that failed - source
      return 2; //no such file or directory
   }
   //open destination file for writing purposes(=_WRONLY);
   //if file does not exist create it as a regular file (=_CREAT)
   //O_EXCL => if this flag  is  specified  in  conjunction with O_CREAT
   //and pathname already exists then open() fails with the error EEXIST
   //, forcing the creation of the file in this call or an error to be thrown

   //mode_t = 0644 = S_IROTH|S_IRGRP|S_IRUSR |S_IWUSR =  others have read permission(4) |
   // group has read permission (40) | user has read permission(200) | user has write permission(400)
   //Note: 200|400 = 600
   fd2 = open(argv[2],O_WRONLY|O_CREAT|O_EXCL,0644);
   //if error occurs opening destination file
   if(fd2 == -1){
      perror(argv[2]);
      close(fd1); //close file descriptor fd1
      return 3; //no such process
   }

   //while there is something to read in the file pointed by fd1 (not EOF)
   //read BUFFER_SIZE bytes into buffer from fd1 and return to nr the number of bytes read
   while((nr = read(fd1,buffer,BUFFER_SIZE)) > 0){
      //writes up to nr bytes from the buffer starting at buffer to the
      //file referred to by fd2
      //if nothing  was  written (0),an error occured(-1) or the number of 
      //bytes written is different from the number of bytes read
      if((nw = write(fd2,buffer,nr)) <= 0 || nw != nr){ 
         perror(argv[2]); //print a system error message with name of file that failed - destination
         close(fd1); //close file descriptor fd1
         close(fd2); //close file descriptor fd2
         return 4;// Interrupted system call
      }
      close(fd1);
      close(fd2);
      return 0;
   }


   
}