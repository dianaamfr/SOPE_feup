#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[])
{
   pid_t pid;
   int status;

   if (argc != 2) {
      printf("usage: %s dirname\n",argv[0]);
      exit(1);
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