#include <stdio.h>
#include <string.h>

void clearCharArray(char array[]);

int main()
{
    char a[30] = "hell000";
    // printf("a[0] = \'%c\'\n",a[5]);
    clearCharArray(a);
    a[0] = '\0';
    clearCharArray(a);
    // printf("a[0] = \'%c\'\n",a[3]);
    // printf("a[0] = \'%c\'\n", a[1]);
    // printf("a = \'%s\'\n", a);
    return 0;
}

void clearCharArray(char array[])
{
    int arrLength = 0;

    while (array[arrLength] != 0)
    {
        arrLength++;
    }
int i =strlen(array);
    printf("Character array has %d elements\n", arrLength); // should give 33
    printf("Character array has %d elements\n", i); // should give 33


    // char * temp;
    // strcpy(temp,array);

    // int len = strlen(array);
    // printf("len = %d\n",len);
    // memset(array, '\0', strlen(array));

    // for (size_t i = 0; i < len-1; i++)
    // {
    //     array[i] = ' ';
    // }
    // array[len] = '\0';
}
