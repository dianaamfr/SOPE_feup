//format specifiers
//pritnf and scanf
//sscanf, sprintf, fgets , puts
//getdelim, getline
//clean input buffer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 10

int main(){
    char a;
    //int b;
    //float c ;
    //double d;
    //char e[MAX_STR_LEN+1];
    //alternativamente:
    //char *e;
    //e = (char*)malloc((MAX_STR_LEN+1)*sizeof(char));
    //size_t f;

    //format specifiers - printf vs scanf (attention to &)
    
    printf("char: ");
    scanf("%c",&a);
    printf("%c\n",a);
   /*
    printf("int: ");
    scanf("%d",&b);
    printf("%d\n",b);

    printf("int: ");
    scanf("%i",&b);
    printf("%i\n",b);

    printf("float: ");
    scanf("%f",&c);
    printf("%f\n",c);

    printf("double: ");
    scanf("%lf",&d);
    printf("%lf\n",d);
    
    //scanf for strings
    //int scanf("%s", stringValue)
    //reads up to the 1 st space, tab or newline (non included in stringValue);
    //the rest remains in the input buffer
    printf("string: ");
    //note that & is not needed because an array is a pointer
    scanf("%s",e); // ex: Diana Freitas (lê Diana e deixa o resto no buffer)
    printf("%s\n",e);
    //no caso de ser usada a alternativa acima
    //free(e);
    
    printf("size_t: ");
    scanf("%zu",&f);
    printf("%zu\n",f);
    */



   /*
    //sscanf
    //int sscanf(const char *s, const char *format, ...);
    int day, year;
    char weekday[20], month[20], dtm[100];

    strcpy( dtm, "Saturday March 25 1989" );
    //reads from string dtm
    //sends formatted output to a string pointed to, by str
    sscanf( dtm, "%s %s %d  %d", weekday, month, &day, &year );// note when & is and is not necessary

    printf("%s %d, %d = %s\n", month, day, year, weekday);
    */



    
    //sprintf
    //int sprintf(char *s, const char *format, ...);
    char buf[20];
    int x = 15, y = 25, z;
    z = x + y;
    sprintf(buf, "Sum of values: %d", z);
    printf("%s", buf);
    



    
    //fgets
    //char * fgets ( char * str, int num, FILE * stream );
    //stops when either num-1 characters are read, NEWLINE character is read or end-of-file is reached
    //whichever comes first
    char mystring [100];

    FILE* fp = fopen("/home/diana/Documents/sope/t01/test_c_revision.txt", "r");
    if (fp == NULL) perror ("Error opening file");
    else {
        //puts
        //int puts(const char *str)
        //writes a string to stdout up to but not including the null character
        //A newline character is appended to the output.
        if (fgets (mystring , 100 , fp) != NULL )
            puts (mystring);
        fclose (fp);
    }


    //getdelim
    //ssize_t getdelim(char **restrict lineptr, size_t *restrict n, int delimiter, FILE *restrict stream);
    /*
    Reads from the stream stream until delimiter is encountered,
    storing the characters in the buffer of size *n pointed to by
    *lineptr, automatically increasing its size as if by realloc 
    to fit the entire input, including the delimiter, and adding a null terminator*/
    /*char *buffer1;
    size_t bufsize1 = 32;
    size_t characters1;

    buffer1 = (char *)malloc(bufsize1 * sizeof(char));
    if( buffer1 == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    printf("Type something: ");
    characters1 = getdelim(&buffer1,&bufsize1,',',stdin);
    //clean input buffer in C
    while ((getchar()) != '\n');
    printf("You typed: '%s'\n",buffer1);
*/


    //getline
    //ssize_t getline(char **restrict lineptr, size_t *restrict n, FILE *restrict stream);

    //example 1
    char *buffer;
    size_t bufsize = 32;
    size_t characters;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    printf("Type something: ");
    characters = getline(&buffer,&bufsize,stdin);
    printf("%zu characters were read.\n",characters);
    printf("You typed: '%s'\n",buffer);

    //example 2

    /*When found in the input sequence, the delimiting character 
    is extracted from the input sequence,but discarded and not written to s.
    If the function stops reading because n characters have been read
    without finding the delimiting character, the failbit internal flag is set (=> cin.clear())
    but the additional characters are removed from the buffer.*/

    return 0;
}