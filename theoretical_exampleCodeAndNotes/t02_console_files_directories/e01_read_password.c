/*Read password without showing it while writing - show * instead of each character*/

#include <termios.h> //termios struct and flags,  tcgetattr(), tcsetattr()
#include <unistd.h> //write(), read(), tcgetattr(), tcsetattr()
#include <string.h> //strlen()

#define MAX_PASSWORD_LEN 20

int main(void){
   //oldterm -> struct to store the original characteristics of a console component
   //term -> struct to store the new characteristics we want to define for a console component
   struct termios term, oldterm;

   int i;
   //pass -> password buffer for 20 characters max(+'/0')
   //ch -> to read each character of the password
   //echo -> the character to show for each char of the passoword that is typed
   char pass[MAX_PASSWORD_LEN+1], ch, echo = '*'; 

   //write up to 11 bytes to standard output file
   write(STDOUT_FILENO, "\nPassword?",11);

   //fill oldterm struct with the characteristics of the standard input file
   tcgetattr(STDIN_FILENO, &oldterm);
   term = oldterm;
   //disable some flags to hide the written password character:

   //ICANON - set canonical mode
   //in this case we disable this flag so we set non canonical mode in which
   //input is available immediately (without the user having to type a line-delimiter character),
   // no input processing is performed, and line editing is disabled

   //ECHO - echo input characters

   //ECHOE - If ICANON is set, the ERASE character erases the preceding input character
   //ECHOK - If ICANON is also set, the KILL  character  erases  the  current line
   //ECHONL - If ICANON is also set, echo the NL character even if ECHO is not set.

   term.c_lflag &= ~(ECHO|ECHOE|ECHOK|ECHONL|ICANON);

   //set the new termios struct 
   tcsetattr(STDIN_FILENO,TCSAFLUSH,&term);

   i=0;
   //read one byte(one char) of the input file at a time
   while(i<MAX_PASSWORD_LEN && read(STDIN_FILENO, &ch, 1) && ch!='\n'){
      pass[i++] = ch; //store it in the password array
      write(STDOUT_FILENO,&echo,1); //write * for each char typed
   }
   pass[i]=0; // add the '/0' char

   //set the old termios struct
   tcsetattr(STDIN_FILENO,TCSANOW,&oldterm);

   //show the password on the screen
   write(STDOUT_FILENO, "\n\nPassword: ", 13); //'/n' counts as a byte
   write(STDOUT_FILENO, pass, strlen(pass));
   write(STDOUT_FILENO,"\n",1);

   return 0;
}
