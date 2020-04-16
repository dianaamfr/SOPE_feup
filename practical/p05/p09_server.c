/* 
 Arquitectura cliente-servidor
 Programa servidor
 
 O servidor deverá criar um FIFO(por exemplo,/tmp/fifo.s) ) e ficar à espera que os clientes lhe enviem comandos e o seu pid.

Os comandos são strings representando programas executáveis que podem ter ou não ter parâmetros na linha de comando.
Quando o servidor lê um destes comandos do FIFO:
- executa‐o (criando um novo processo)
- direccionando a sua saída standard para um ficheiro auxiliar

Após a execução envia o conteúdo do ficheiro auxiliar produzido (ou uma mensagem de erro, se não conseguiu executar o comando)
para o cliente através de outro FIFO criado pelo cliente.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <signal.h>
#include <errno.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_FIFO_NAME 25
#define MAX_CMD_ARGS 20
#define MAX_ARG_SIZE 25
#define MAXLINE 1000 

struct msg{
   char cmd[MAXLINE];
   pid_t pid;
}; 

int main(){
   int fd1, fd2, fd3;
   struct msg clientMsg; 
   char line[MAXLINE]; 

   if(mkfifo("/tmp/fifo.s",0660) < 0){
      if (errno == EEXIST)
         printf("FIFO '/tmp/fifo.s' already exists\n");
      else printf("Can't create FIFO\n"); 
   }
   else 
      printf("FIFO '/tmp/fifo.s' sucessfully created\n"); 


   do{
      if ((fd1 = open("/tmp/fifo.s",O_RDONLY)) != -1)
         printf("FIFO '/tmp/fifo.s' openned in READONLY mode\n");

      read(fd1,&clientMsg,sizeof(struct msg));
      close(fd1);

      // Build command

      int i = 0, j = 0, l = 0;
      char * args[MAX_CMD_ARGS];
      char cmd[MAX_ARG_SIZE];
      memset(cmd, 0, MAX_ARG_SIZE);
      for (int k = 0; k < MAX_CMD_ARGS; k++) 
         args[k] = (char *)malloc( MAX_ARG_SIZE * sizeof(char)); 

      
      while(clientMsg.cmd[l] != '\n'){
         if(clientMsg.cmd[l] == ' '){
            cmd[j] = '\0';
            memcpy(args[i],cmd,MAX_ARG_SIZE);
            //args[i] = cmd; 
            memset(cmd, 0, MAX_ARG_SIZE);
            i++;
            j=0;
         }
         else{
            cmd[j] = clientMsg.cmd[l];
            j++;
         }
         l++;
      }
      cmd[j] = '\0';
      memcpy(args[i],cmd,MAX_ARG_SIZE);
      i++;
      args[i] = '\0';

      char fifoName[MAX_FIFO_NAME];
      sprintf(fifoName,"/tmp/fifo.%d",clientMsg.pid);
      if ((fd2 = open(fifoName,O_WRONLY)) != -1)
         printf("FIFO '%s' openned in WRITEONLY mode\n",fifoName);

      pid_t pid = fork();

      if(pid == 0){ // Child

         if((fd3 = open("/tmp/aux",O_CREAT|O_WRONLY, 0644)) == -1 ){
            fprintf(stderr,"Error opening aux file!\n");
            exit(1);
         } else printf("File aux openned in WRITEONLY mode\n");

         dup2(fd3,STDOUT_FILENO);
         close(fd3);

         execvp(args[0], args);
         exit(1);
         
      }
      else if(pid > 0){ // Parent
         int status;
         wait(&status);

         if(WEXITSTATUS(status) == 1){
            printf("error\n");
            write(fd2, "Error. The server could not execute the command.\n",49);
         }
         else{

            if((fd3 = open("/tmp/aux",O_RDONLY)) == -1 ){
               fprintf(stderr,"Error opening aux file!\n");
               exit(1);
            } else printf("File aux openned in READONLY mode\n");

            printf("Reading file\n");
            while(read(fd3,line,MAXLINE) != 0){
               int n = strlen(line); 
               if((write(fd2, line, n)) != n)
               {
                  fprintf(stderr, "Write to pipe failed.\n");
                  exit(1);
               }
               memset(line, '\0',MAXLINE);
            }
         }
         close(fd2); 
         close(fd3); 
      }
      else{
         fprintf(stderr,"Fork error!\n");
         exit(1);
      }
      
   } while (1); 

   exit(0); 
}