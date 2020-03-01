/*copy file to screen or to other file depending on the number of arguments*/
/*progName source => mostrar no ecrã*/
/*progName source destination => copiar de source para destination*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[]){
   int fd1, fd2, nr, nw;
   unsigned char buffer[BUFFER_SIZE];

   //if number of arguments is not correct
   if((argc != 2) && (argc !=3)){
      printf("Usage: %s <source> OR %s <source> <destination>\n",argv[0],argv[0]);
      return 1; //operation nor allowed
   }
   //open file referred by 1st arg in read only mode
   fd1 = open(argv[1],O_RDONLY);
   //if any error occurs opening the file
   if(fd1 == -1){
      perror(argv[1]); //throw error with the name of the file
      return 2; //no such file error
   }

   if(argc == 3){
      //open file referred by 2nd arg in write only mode
      //O_CREAT and O_ECL => if file with that name already exists throw error, otherwise create it 
      //0644 = > set permissions - user can read and write and others and group can read
      fd2 = open(argv[2], O_WRONLY|O_CREAT|O_EXCL,0644);
      //if error occurs 
      if(fd2 == -1){
         perror(argv[2]); //throw error with info about the name of the file
         close(fd1); //close the source file
         return 3; //no such process error
      }
      //redirect STDOUT_FILENO (standard output /screen) to the file with fd2 descriptor
         /*!!!!!!!!!!!!*/
         dup2(fd2,STDOUT_FILENO);
         /*!!!!!!!!!!!!*/
   }
      //while there are still bytes to read(not EOF /end of file/0)
      //and no error are thrown (-1)
   while((nr = read(fd1,buffer,BUFFER_SIZE))>0){
      //if nothing  was  written (0),an error occured(-1) or the number of 
      //bytes written is different from the number of bytes read
      
      /*!!!!!!!!!!!! - difference from previous example - related to the use of dup2*/
      if((nw = write(STDOUT_FILENO, buffer, nr)) <= 0 || nw !=nr){
         perror(argv[2]);
         close(fd1);
         close(fd2);
         return 4; //Interrupted system call
      }
      close(fd1);
      if(argc == 3)
         close(fd2);
      return 0;
   }
}