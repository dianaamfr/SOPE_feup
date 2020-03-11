#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*

1)Se o argumento é um directório existente:

My child is going to execute command"ls -laR ../p03"
../p03:
total 264
drwxr-xr-x 2 diana diana 4096 mar 10 22:15 .
drwxr-xr-x 5 diana diana 4096 mar 10 21:51 ..
.....
-rw-rw-r-- 1 diana diana  662 mar 10 22:15 p9a.c
My son exited with EXIT CODE 0 


2)Se o argumento é um directório inexistente:

My child is going to execute command"ls -laR ../p0"
ls: cannot access '../p0': No such file or directory
My son exited with EXIT CODE 2 

3)o argumento é um directório existente, com   muitos ficheiros, e o processo‐filho foi terminado
recorrendo ao comando kill(para ter tempo de dar este comando, deverá indicar como
argumento um directório que contenha muitos ficheiros)



*/

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
      printf("My son exited with EXIT CODE %d \n",WEXITSTATUS(status));  
   }
   else if (pid == 0){
      char * args[]={"ls","-laR",argv[1],NULL};
      execvp("ls",args);
      printf("Command not executed !\n");
      exit(1);
   }
   exit(0);
} 