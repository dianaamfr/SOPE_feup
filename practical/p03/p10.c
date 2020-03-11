#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[], char *envp[])
{
   pid_t pid;
   int status;
   int fd;

   if (argc != 2 && argc != 3) {
      printf("usage: %s dirname OR %s dirname destFile\n",argv[0],argv[0]);
      exit(1);
   }

   if(argc == 3){
      //open file referred by 2nd arg in write only mode
      //O_CREAT and O_ECL => if file with that name already exists throw error, otherwise create it 
      //0644 = > set permissions - user can read and write and others and group can read
      fd = open(argv[2], O_WRONLY|O_CREAT|O_EXCL,0644);
      //if error occurs 
      if(fd == -1){
         perror(argv[2]); //throw error with info about the name of the file
         return 3; //no such process error
      }
      //redirect STDOUT_FILENO (standard output /screen) to the file with fd descriptor
         /*!!!!!!!!!!!!*/
         dup2(fd,STDOUT_FILENO);
         /*!!!!!!!!!!!!*/
   }

   pid=fork();
   if (pid > 0){
      printf("My child is going to execute command\"ls -laR %s\"\n", argv[1]);
      wait(&status);
      if (WIFEXITED(status)) //avaliada como verdadeira se o filho terminou normalmente
         printf("normal termination, exit status = %d\n", WEXITSTATUS(status)); 
      else if (WIFSIGNALED(status)){//verdadeira se o filho terminou anormalmente,porque recebeu um sinal que não tratou
         printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
         printf("abnormal termination, signal number = %d\n",WTERMSIG(status));
      }
   }
   else if (pid == 0){
      char * args[]={"ls","-laR",argv[1],NULL};
      execvp("ls",args);
      printf("Command not executed !\n");
      exit(1);
   }
   exit(0);
} 