#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_PASSWORD_LENGTH 25

int main(){
   struct termios oldterm, term;
   char password[MAX_PASSWORD_LENGTH + 1]; // length 25 max (plus '\0')
   char toEcho = '*', c;
   char errorMessage[] = "\nReading error!\n";

   write(STDOUT_FILENO,"\nPassword? ",11); // ask for the password

   //fill the termios structure with current configuration of the input stream
   tcgetattr(STDIN_FILENO,&oldterm);

   //disabling c_lflag flag constants:
   term = oldterm;
   //Raw/non canonical mode(~ICANON) - default is canonical and that must not be the case:
   //Desabilitar modo default
   //input is available immediately (without the user having to type a line-delimiter character)
   //input characters are passed one by one to the program
   //don't echo input charcters (~ECHO)
   term.c_lflag &= ~(ECHO|ICANON|ECHOE|ECHOK|ECHONL);

   //set new term => to no only not show the input character but to send it one by one to the progr
   //TCSAFLUSH => the  change  occurs  after  all  output  written  to  the object
   //referred by fd has been transmitted, and all input that has been
   //received  but  not  read  will be discarded before the change is made.
   tcsetattr(STDIN_FILENO,TCSAFLUSH,&term);

   int i = 0;

   //read the password until the max length is achived, the new line character is read
   //or a error occurs reading
   while(i < MAX_PASSWORD_LENGTH){
      int readReturn = read(STDIN_FILENO,&c,1);
      if(readReturn > 0 && c != '\n'){
         password[i] = c;
         write(STDOUT_FILENO,&toEcho,1);
         i++;
      }
      else if(readReturn == -1){
         perror(errorMessage);
         exit(1);
      }
      else if(c == '\n') break;
   }
   password[i] = '\0';

   //set the termios struct back to its original values
   //TCSANOW makes the change immediatly
   tcsetattr(STDIN_FILENO,TCSANOW,&oldterm);

   //show password on screen
   write(STDOUT_FILENO,"\nPassword: ",11);
   write(STDOUT_FILENO,password,strlen(password)); 
   write(STDOUT_FILENO,"\n",1);
   return 0;
}