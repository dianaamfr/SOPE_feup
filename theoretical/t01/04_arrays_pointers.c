#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 10

int main()
{
    int i;
    int a[MAX_LEN];
    int *b;

    for (i = 0; i < MAX_LEN; i++)
        a[i] = i;

    printf("a[] = \n");
    for (i = 0; i < MAX_LEN; i++)
        printf("a[%d]=%d\n", i, *(a + i));

    b = a;

    printf("b[] = a[] = \n");
    for (i = 0; i < MAX_LEN; i++)
        printf("b[%d]=%d\n", i, b[i]);

    for (i = 0; i < MAX_LEN; i++)
        a[i] = i+5;


    //mudando o array a muda o b também pois apontam para o mesmo endereço
    printf("a[] = \n");
    for (i = 0; i < MAX_LEN; i++)
        printf("a[%d]=%d\n", i, *(a + i));

    printf("b[] = a[] = \n");
    for (i = 0; i < MAX_LEN; i++)
        printf("b[%d]=%d\n", i, b[i]);

    return 0;
}