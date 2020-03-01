#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 10 // TRY WITH OTHER VALUES

int main()
{
    // Strings declarations
    char name1[MAX_NAME_LENGTH] = "Ann Sousa"; 
    // try with a longer name => warning: initializer-string for array of chars is too long
    char name2[MAX_NAME_LENGTH];
    char *name3; // assigned to a constant (see below)
    char *name4;
    char *name5 = NULL;

    printf("name1=%s\n", name1);
    //name2="John";
    // ‐‐> COMPILATION ERROR => assignment to expression with array type

    name3 = "John Dalton";
    printf("name3=%s\n", name3);

    name4 = (char *)malloc(MAX_NAME_LENGTH*sizeof(char));
    printf("Nome4 ? "); fgets(name4, MAX_NAME_LENGTH, stdin);
    printf("name4=%s\n", name4);

    // WHICH IS THE DIFFERENCE AMONG THE 3 SEQUENCES OF STATEMENTS BELOW ?

    //1) ‐
    // name5=name4; //they point to the same address and,therefore, if name4 is changed so is name5
    // printf("Nome4 ? "); fgets(name4, MAX_NAME_LENGTH, stdin);

    //2) ‐ THE PROGRAM MAY CRASH ... WHY?
    //Segmentation fault(Core dumped) => accessing memory that “does not belong to you.”
    //cause of the error: no memory was allocated for name5
    //strcpy(name5,name4); // SYNTAX: strcpy(destination,source)

    //3) ‐ CORRECTION OF THE ERROR FROM 2) ... WHY?
    name5 = (char *)malloc((strlen(name4) + 1)*sizeof(char));
    strcpy(name5, name4); // SYNTAX: strcpy(destination,source)
    printf("name5=%s\n", name5);

    //4)
    name5 = &name1[4]; //name 5 points to the index 4 of name1
    //name1[4] = 'F'; //if name1 is changed so is name5
    printf("name5(new)=%s\n", name5);
    
    return 0;
}