#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#define WRITE 1
#define READ 0
#define BUF_SIZE 200

void full_copy(int from, int to) {
   char buffer[BUF_SIZE];
   size_t n;
   while ((n = read(from, buffer, BUF_SIZE)) > 0)
      write(to, buffer, n);
   close(from);
   close(to);
}

int main(int argc, char * argv[]){
   if(argc != 2){
      fprintf(stderr,"Usage: %s <filename>", argv[0]);
      return 1;
   }

   int fd1, fd2[2];

   if(pipe(fd2) < 0){
      fprintf(stderr,"Pipe error");
      return 1;
   }

   pid_t pid = fork();

   if(pid == 0){ // CHILD
      close(fd2[WRITE]);

      dup2(fd2[READ],STDIN_FILENO);
      close(fd2[READ]);

      execlp("cat", "cat", NULL);
      fprintf(stderr,"Exec error");
      return 1;
   }
   else if(pid > 0){ // PARENT
      close(fd2[READ]);

      fd1 = open(argv[1],O_RDONLY);
      full_copy(fd1,fd2[WRITE]);
   }
   else {
      fprintf(stderr,"Fork error");
      return 1;
   }
   
   return 0;
}