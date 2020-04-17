/* 
 Arquitectura cliente-servidor
 Programa cliente
 
 O cliente simplesmente:
 - cria o FIFO para receber a resposta (/tmp/fifo.pid, em que pid é o identificador do cliente)
 - envia o seu pid para o servidor e o comando para este executar
 - espera pela resposta 
 - quando esta chegar, mostra‐a no écran
 - termina.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h> 
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_MSG_LEN 100 
#define MAX_FIFO_NAME 25
#define MAX_CMD_ARGS 20
#define MAX_ARG_SIZE 25
#define MAXLINE 1000 

struct msg{
   char cmd[MAXLINE];
   pid_t pid;
};

int main(){

   int fd1, fd2;
   struct msg clientMsg; 
   char fifoName[MAX_FIFO_NAME];
   sprintf(fifoName,"/tmp/fifo.%d",getpid());
   char line[MAXLINE]; 

   if(mkfifo(fifoName,0660) < 0){
      if (errno == EEXIST)
         printf("FIFO '%s' already exists\n",fifoName);
      else printf("Can't create FIFO\n"); 
   }
   else 
      printf("FIFO '%s' sucessfully created\n",fifoName); 

   printf("command ? ");
   fgets(clientMsg.cmd,MAX_MSG_LEN,stdin);
  
   clientMsg.pid = getpid();

   fd1 = open("/tmp/fifo.s",O_WRONLY);
   if (fd1 == -1) {
      printf("Oops !!! Service is closed !!!\n");
      exit(1);
   }

   write(fd1,&clientMsg,sizeof(struct msg));
   close(fd1); 

   if ((fd2 = open(fifoName,O_RDONLY)) != -1)
      printf("FIFO '%s' openned in READONLY mode\n",fifoName);
   
   while(read(fd2,line,MAXLINE) != 0) printf("%s\n",line); 
   close(fd2);
   
   exit(0);
}