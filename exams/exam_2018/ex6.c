// Exam 2018 - exercise 6

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>  
#include <signal.h>
#include <string.h>


char filename[200];
char destination_dir[200];

int process_dir(char *dirname){
   DIR *dir;
   struct dirent *entry;
   struct stat statbuf;

   if (!(dir = opendir(dirname))) return 1;

   while ((entry = readdir(dir)) != NULL) {
      char path[1024];
      // ‐‐‐ BLOCO A ‐‐‐
      sprintf(path, "%s/%s", dirname, entry->d_name);
      stat(path, &statbuf);

      if (S_ISDIR(statbuf.st_mode)) { // se 'entry' for um diretório
         if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

         // cria um processo que invoca process_dir()
         pid_t pid = fork();
         switch(pid){
            case 0:
               process_dir(path);
               break;
            default:
               break;
         }

      }  
      // ‐‐‐ FIM DO BLOCO A ‐‐‐
      // ‐‐‐ BLOCO B ‐‐‐
      else if(S_ISREG(statbuf.st_mode)) { // se 'entry' for um ficheiro regular
      //...
         if(strstr(entry->d_name, filename) != NULL) { // se o nome do ficheiro contiver filename
            // cria um processo que invoca o utilitário 'cp'
            pid_t pid = fork();
            switch(pid){
               case 0:
                  execlp("cp", "cp", path, destination_dir, NULL);
                  break;
               default:
                  break;
            }
         }
      }
      // ‐‐‐ FIM DO BLOCO B ‐‐‐
   }
   return 0;
}

int main(int argc, char * argv[]){
   if(argc != 4){
      fprintf(stderr,"Usage: %s <dir_to_search> <filename> <destination_dir>",argv[0]);
      return 1;
   }

   strcpy(destination_dir,argv[3]);
   strcpy(filename, argv[2]);

   struct sigaction action;
   action.sa_handler = SIG_IGN;
   sigemptyset(&action.sa_mask);
   action.sa_flags = 0;
   sigaction(SIGINT, &action, NULL);

   process_dir(argv[1]);

   return 0;
}