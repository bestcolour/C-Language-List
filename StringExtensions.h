#include <ctype.h>
#include <stdio.h>
#include <string.h>
// https://www.geeksforgeeks.org/removing-trailing-newline-character-from-fgets-input/

// Checks if a string is a number. Returns 0 if it is not else it will return the number of digits found in the string.
int isNumber(char *string)
{
    int length = strlen(string);

    int hasFoundNumber = 0;

    for (size_t i = 0; i < length; i++)
    {

        // printf("%d)\"%c\"\n",i,string[i]);
        if (isdigit(string[i]))
        {
            // Increment to show that a digit was found
            hasFoundNumber++;
        }
        // Else if char is not empty and is not a whitespace
        else if (string[i] != '\0' && !isblank(string[i]))
        {
            hasFoundNumber = 0;
        }
    }

    return hasFoundNumber;
}

// Converts a digit char to its respective int value. Returns -1 if unable to convert.
int digitCharToInt(char ch)
{
    if (!isdigit(ch))
    {
        return -1;
    }
    return ch - '0';
}

// Finds the first substring in the string. Returns the array position of where the word starts in the line else return -1
int find_FirstSubstr_InStr(char *str, char *word)
{
    // Need to declare their values else the next time I use this function, flag may still be = 1
    int i, j = 0, Flag = 0;

    // printf("Looping thru: \n%s\n. Flag Value = %d", str,Flag);

    for (i = 0; str[i] != '\0'; i++) // Check the chars in this line
    {
        // printf("%d) str[i] = \'%c\' word[0] = \'%c\'\n", i, str[i], word[0]);

        if (str[i] == word[0]) // Find the first char of the word in line
        {
            // printf("I'm in i = %i \nstr[i] = \'%c\' word[0] = \'%c\'\n", i, str[i], word[0]);
            Flag = 1;

            // Check if word existing is sus
            for (j = 0; word[j] != '\0'; j++)
                if (str[i + j] != word[j])
                {
                    Flag = 0; // If not sus
                    break;
                }
        }
        if (Flag == 1)
        {
            // printf("i -> %d\n", i);
            return i;
        }
    }
    return -1;
}

// Function to implement substring function in C
char *substring(char *destination, const char *source, int beg, int n)
{
    // extracts `n` characters from the source string starting from `beg` index
    // and copy them into the destination string
    while (n > 0)
    {
        // sets the value of destination to be (source + beg * sizeof(char))'s value
        *destination = *(source + beg);

        // Update both destination and source's address for the next loop
        destination++;
        source++;
        n--;
    }

    // null terminate destination string
    *destination = '\0';

    // return the destination string
    return destination;
}

void removeLineBreak(char *str)
{
    int len = strlen(str);
    int i;
    do
    {
        i = strcspn(str, "\n");

        str[i] = ' ';
    } while (i != len);
}

void remove_spaces(char *s)
{
    char *d = s;
    do
    {
        while (*d == ' ')
        {
            ++d;
        }
    } while (*s++ = *d++);
}

void clearCharArray(char array[])
{
    memset(array, '\0', strlen(array));
}

// Removes a string from another string. Returns the string of the edited sentence.
void removeString(char *source, int wordPos, int wordLength)
{
    int i, j, k = 0;
    // printf("%d", strlen(array));
    // Clear the word
    for (j = 0; j < wordLength; j++)
    {
        i = wordPos + j; // Next character position to clear

        *(source + i) = ' ';
    }

    // Get the number of chars beind the removed word
    i = strlen(source) - wordLength - wordPos + 1;
    // printf("%d\n", i);
    for (j = 0; j < i; j++)
    {
        k = j + wordPos + wordLength; // The index of the next char to be pushed forward
        *(source + j + wordPos) = *(source + k);
        *(source + k) = '\0';
    }
}

char *insertStr(char *destination, char *sourceA, char *sourceB, int n)
{
    strncpy(destination, sourceA, n);
    destination[n] = '\0';
    strcat(destination, sourceB);
    strcat(destination, sourceA + n);

    return destination;
}

void remove_Orphan_WhiteSpaces(char *destination, char *source)
{
    int i = 0, j = strlen(source) - 1, k = 0;

    // Iterate String until last leading space character
    while (source[i] == ' ' || source[i] == '\t' || source[i] == '\n')
        i++;

    // Iterate String until last trailing space character
    while (source[j] == ' ' || source[j] == '\t' || source[j] == '\n')
        j--;

    // Run a for loop from index until the original
    // string ends and copy the content of str to str1
    for (; i <= j; i++)
    {
        destination[k] = source[i];
        k++;
    }

    // Insert a string terminating character
    // at the end of new string
    destination[k] = '\0';
}