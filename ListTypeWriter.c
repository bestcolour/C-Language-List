#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "./StringExtensions.h"

#pragma region ===== Struct =====
typedef struct memberData
{
    char type[32];
    char modifier[32];
    char variableName[32];
} memberData;
#pragma endregion

#pragma region ===== Global Vars =====
static char elementName[20]; // The name of the element the list is going to hold. Examples include "int, double, char *,bool" or some struct names "jobData"

// static char elementMembers[32][256]; // Holds the declared element members if the element is a struct.

static memberData elementMemberData[32];

static char elementDefinition[512];   // The string value of the element's definition if the user inputs a struct
static char elementDefaultValue[512]; // The default value tof the element declared by the user.

static int elmtMemberSize; // The number of members in the element. Is 0 if the user doesn't put struct data type as element
static char listName[24];
const char DEFAULT_LISTNAME[4] = "List";
static char defaultType_ValueName[100];

static bool isDoneAssigningDefVal = false, isDoneAssigningDefaultVal = false, isDoneAssigningPrintCondition = false, isDoneAssigningPrintOutput = false;
static int isDoneWritingFindFunc = 0;
static int isDoneRenamingDefValVar = 0;
// const char defTypeValVarName[19];

const int FILEBUFFER_SIZE = 300;

#pragma region-- -- -Data Type-- -- -
enum dataType
{
    STRUCT, // MUST BE PLACED FIRST IN THE TYPE_NAMES ARRAY
    POINTER,
    INT,
    FLOAT,
    CHAR,
    DOUBLE,
    LONG
};
const int TYPELENGTH = 7;
char *TYPE_DECLARATION[7] = {"struct", "*\0", "int", "float", "char", "double", "long"};
#pragma endregion

#pragma endregion

#pragma region ===== Functions =====

void declareCode(); // Asks the how they want to write their list code.

char *writeCode(char *line);                                                                     // Checks for any special definitions or words that need to be changed in the Original List file and then changes it according to the user's naming
void writeCode_printOutPut_ConcatForStructCase(char *destination, char *variableName, int type); // Handles concating the output code for print function when the element is a struct.
void writeCode_printOutPut_ConcatForBasicCase(char *destination, char *variableName, int type);  // Handles concating the output code for print function when the element is a basic data type.

#pragma endregion

int main()
{
#pragma region ===== Variables & Constants =====
    const char ORIGINAL_LIST_PATH[100] = "List.h";
    FILE *pFStart, *pFEnd;
    int i;
    char buffer[FILEBUFFER_SIZE], newListPath[100];

#pragma endregion

#pragma region ===== Getting Information Ready =====

    pFStart = fopen(ORIGINAL_LIST_PATH, "r"); // Read Original list

    if (pFStart == NULL)
    {
        printf("There is no such file called \"%s\"\n", ORIGINAL_LIST_PATH);
        return 0;
    }

    printf("Input path and name for the duplicate to be in.\n");
    scanf("%s", &newListPath);
    scanf("%*c");

    pFEnd = fopen(newListPath, "a");

    // If there is some error with creating the file (maybe due to naming)
    if (pFEnd == NULL)
    {
        strcpy(newListPath, "NewListType.h");
        pFEnd = fopen(newListPath, "a");
    }

    declareCode(); // Getting Info From User
#pragma endregion

#pragma region ===== Writing Files =======
    // Will return null if there is nth else to read
    int l = 0;
    while (fgets(buffer, sizeof(buffer), pFStart) != NULL)
    {
        // printf("%d)%s", l, buffer);

        // Do your custom variable naming magic here
        strcpy(buffer, writeCode(buffer));

        // printf("%d)%s\n",     l, buffer);
        // Append to the end file
        fputs(buffer, pFEnd);
        l++;
    }

    fclose(pFStart);
    fclose(pFEnd);
#pragma endregion

    printf("\nEnded\n");

    // For debugging
    // if (remove(newListPath) == 0)
    // {
    //     printf("That file was deleted successfully\n");
    // }
    // else
    // {
    //     printf("That file was not deleted\n");
    // }

    return 0;
}

void declareCode()
{
    int i, j, k, l, n;
    char currWord[30];
    bool boolA;
#pragma region-- -- -Getting Element Values-- -- -

#pragma region _____ Element Name _____
    do
    {
        clearCharArray(elementDefinition);
        clearCharArray(currWord);
        i = -1;
        printf("===== Declare your list element definition =====\nPress '`' and 'Enter' to end input. \n(For eg. If you want your element to be a struct, type down all the code for it to be a struct and copy and paste it here. \nOr if you just want it to be a 'int', type 'int')\n");
        scanf("%[^`]s", elementDefinition);
        scanf("%*c");
        // printf("=== Printing ===\n Element Definition: %s\n", elementDefinition);

        for (j = 0; j < TYPELENGTH; j++)
        {
            l = j;
            strcpy(currWord, TYPE_DECLARATION[j]);
            // printf("type: %d Type Representation: %s\n", l, TYPE_DECLARATION[j]);
            i = find_FirstSubstr_InStr(elementDefinition, currWord);

            if (i != -1)
                break;
        }

    } while (i == -1);

    printf("=== Printing ===\nElement Definition: \'%s\'\n", elementDefinition);

    switch (l)
    {
    case STRUCT:
        i += strlen(currWord) + 1; // This is the position of first alphabet of the element's name (Eg. "struct" is 6 words and add a whitespace is 7)

        j = find_FirstSubstr_InStr(elementDefinition, "{");  // This is the position of the '{'
        substring(elementName, elementDefinition, i, j - i); // Isolate the string to read only everything within the curly brackets
        break;

    default: // For Basic Data types like double, int, bool and char *
        strcpy(elementName, elementDefinition);
        break;
    }

    removeLineBreak(elementName);
    remove_spaces(elementName);
    printf("=== Printing ===\nElement Name: \'%s\'\n", elementName);

    // printf("=== Printing ===\ni: %d j: %d", i,j);

#pragma endregion

#pragma region _____ Element Default Value _____

    printf("===== Defining your element's default value =====\n\nFor example if your element is a struct with an int and char[] variables, input with the curly braces\n{INT_MIN, \"DEFAULT_VALUE\"}\n\nIf your element is a basic value type like an int, input without curly brackets\nINT_MIN\n\nOr if your type is a \'char *\',input with \"\",\n\"DEFAULT string\"\n\n\nPress '`' and 'Enter' to end input\n");
    scanf("%[^`]s", elementDefaultValue);
    scanf("%*c");
    removeLineBreak(elementDefaultValue);
    remove_Orphan_WhiteSpaces(elementDefaultValue, elementDefaultValue);
    printf("=== Printing ===\nElement Default Value: \'%s\'\n", elementDefaultValue);

#pragma endregion

#pragma region _____ Getting Element Member(s) _____
    clearCharArray(currWord);
    i = k = n = 0;
    // boolA = false; // Let A represent whether the currword is recording is a pointer type or not.

    switch (l) // l is the type of the element
    {
    case STRUCT:
    {
        strrev(elementDefinition);

        j = find_FirstSubstr_InStr(elementDefinition, "}"); // This is the position of the '{'
        j++;                                                // Now, from index j to i in elementDefinition is purely words for the declaration of vars

        for (;; j++) // Read each char from the end to the start of the definition
        {
            if (n == 3)
                break;

            if (elementDefinition[j] == '\0' || elementDefinition[j] == '\n')
                continue;

            switch (n) // n represents the thing that is being recorded within the current loop cycle. 0 = var name, 1 = type, 2 = modifier and 3 = break out of for loop and switch
            {
            case 0: // var name
#pragma region Recording for VariableName
            {
                if (elementDefinition[j] == ';') // Skip the first ';'
                    continue;

                if (elementDefinition[j] == ' ' && k > 0) // When this condition is met, it means that variableName is rdy to be recorded
                {
                    // Reverse the recorded currWord
                    strrev(currWord);
                    strcpy(elementMemberData[i].variableName, currWord);
                    // printf("Recorded var name: \'%s\'\n", currWord);

                    clearCharArray(currWord);
                    k = 0;
                    n = 1;         // Switch to recording types
                    boolA = false; // Let boolA represent the state of knowing whether a type is unknown = false, pointer or normal type  = true.
                    continue;
                }

                // Else, record this character into currWord
                // printf("Curr: \'%c\'\n", elementDefinition[j]);
                currWord[k] = elementDefinition[j];
                // printf("CurrWord: \'%s\' Last k index: \'%d\'\n", currWord, k);
                k++;
            }
#pragma endregion
                continue;

            case 1: // type
#pragma region Recording for Type
            {
                switch (boolA) // Let boolA represent the state of knowing whether a type is unknown = 0, pointer = 1 or normal type = 2.
                {
                case false: // Unknown
                {
                    // Since var name uses elementDefinition[j] == ' ' to determine where to stop, it actually doesnt record the ' ' and skips it hence no matter what, the next j character will belong to type and not be ' '
                    if (elementDefinition[j] == '*') // Check if type is a pointer
                    {
                        boolA = true;
                        currWord[k] = elementDefinition[j];
                        k++;
                        j++; // Skip one loop
                        currWord[k] = elementDefinition[j];
                        k++; // Prepare for next loop
                        continue;
                    }

                    // type is not a pointer
                    boolA = true;
                    // record this character into currWord
                    // printf("Curr: \'%c\'\n", elementDefinition[j]);
                    currWord[k] = elementDefinition[j];
                    // printf("CurrWord: \'%s\' Last k index: \'%d\'\n", currWord, k);
                    k++;
                }
                    continue;
                case true: // Is a pointer
                {
                    if (elementDefinition[j] == ' ') // Reached the end of type
                    {
                        // record the word after whitespace into type
                        strrev(currWord);
                        remove_Orphan_WhiteSpaces(currWord, currWord);

                        strcpy(elementMemberData[i].type, currWord);
                        // printf("Recorded type: \'%s\'\n", currWord);

                        clearCharArray(currWord);
                        k = 0;
                        n = 2; // Go to record modifier
                        continue;
                    }

                    // Else just keep recording
                    //  printf("Curr: \'%c\'\n", elementDefinition[j]);
                    currWord[k] = elementDefinition[j];
                    // printf("CurrWord: \'%s\' Last k index: \'%d\'\n", currWord, k);
                    k++;
                }
                    continue;
                }
            }
#pragma endregion
                continue;

            case 2: // modifier
#pragma region Recording for Modifier
            {
                if (elementDefinition[j] == '{') // if loop has reached the end of the struct declaration
                {
                    // Reverse the recorded currWord
                    strrev(currWord);
                    remove_Orphan_WhiteSpaces(currWord, currWord);

                    strcpy(elementMemberData[i].modifier, currWord);
                    // printf("last Modifier: \'%s\'\n", currWord);
                    n = 3; // break out of switch and for loop
                    break;
                }

                if (elementDefinition[j] == ';') // If reached the end of a line declaration, record the word and prepare for next var name
                {
                    strrev(currWord);
                    remove_Orphan_WhiteSpaces(currWord, currWord);

                    strcpy(elementMemberData[i].modifier, currWord);
                    // printf("Recorded Modifier: \'%s\'\n", currWord);

                    clearCharArray(currWord);
                    k = 0;

                    i++;
                    n = 0;
                    continue;
                }

                // Else, record this character into currWord
                // printf("Curr: \'%c\'\n", elementDefinition[j]);
                currWord[k] = elementDefinition[j];
                // printf("CurrWord: \'%s\' Last k index: \'%d\'\n", currWord, k);
                k++;
            }
#pragma endregion
                continue;

            default:
                break;
            }
        }

        // Record size of the array
        elmtMemberSize = i + 1;
        printf("elmtMmbSize = \'%d\'\n", elmtMemberSize);
        strrev(elementDefinition); // undo the reversal
    }
    break;

    default: // For basic datatype, there will be no element members
        elmtMemberSize = 0;
        break;
    }

    for (i = 0; i < elmtMemberSize; i++) // Debug
        printf("variableName \'%s\' type: \'%s\' modifier: \'%s\'\n", elementMemberData[i].variableName, elementMemberData[i].type, elementMemberData[i].modifier);

#pragma endregion

#pragma endregion

#pragma region-- -- -Getting List Values-- -- -
    strcpy(listName, "");               // listName = elementName
    strcpy(listName, elementName);      // listName = elementName
    strcat(listName, DEFAULT_LISTNAME); // listName = "<elementName>List"
#pragma endregion

    strcpy(defaultType_ValueName, listName);
    strcat(defaultType_ValueName, "_DEFAULT_TYPE_VALUE");
}

char *writeCode(char *line)
{
    int i, j, k = 0;
    char stringA[FILEBUFFER_SIZE], stringB[FILEBUFFER_SIZE];
    bool boolA;
    // printf("Line = %s\n", line);
#pragma region-- -- -(1) Rename "DEFAULT_TYPE_VALUE" -- -- -
    do
    {
        // if (isDoneRenamingDefValVar == 2)
        // break;

        i = find_FirstSubstr_InStr(line, "DEFAULT_TYPE_VALUE");
        if (i == -1)
            break;

        isDoneRenamingDefValVar++;
        // printf("isDoneRenamingDefValVar: %d\n", isDoneRenamingDefValVar);

        // Replace word
        strcpy(stringA, line);
        removeString(stringA, i, strlen("DEFAULT_TYPE_VALUE"));
        insertStr(stringB, stringA, defaultType_ValueName, i);
        strcpy(line, stringB);
        break;
    } while (1);

#pragma endregion

#pragma region-- -- -(2) Write the definition of element-- -- -
    if (elmtMemberSize != 0) // Only do this if element is not of basic datat ype
    {
        strcpy(stringA, "===== Definitions =====");

        i = find_FirstSubstr_InStr(line, stringA);
        if (i != -1)
        {
            i += strlen(stringA) - 1;
            strcat(line, "\n");
            strcat(line, elementDefinition);
            strcat(line, "\n");
        }
    }

    // Assign Default Value variable
    if (!isDoneAssigningDefVal)
    {
        strcpy(stringA, defaultType_ValueName);
        strcat(stringA, " = ");
        i = find_FirstSubstr_InStr(line, stringA);
        if (i != -1)
        {
            isDoneAssigningDefVal = true;

            i += strlen(stringA); // get the index of the character behind the '='
            clearCharArray(stringB);

            // insert elementDefaultValue declared by the user
            strcpy(stringA, line);
            // printf("Char: \'%c\'\n", line[i]);
            // printf("String a: \'%s\'\n", stringA);

            insertStr(stringB, stringA, elementDefaultValue, i);
            // printf("String b: \'%s\'\n", stringB);
            strcpy(line, stringB);
        }
    }

#pragma endregion

#pragma region-- -- -(3) All instance of the string 'renameToElmtName' -- -- -

    while (1)
    {
        strcpy(stringA, "renameToElmtName");
        i = find_FirstSubstr_InStr(line, stringA);

        if (i == -1)
            break;

        j = strlen(stringA);
        // Remove word
        removeString(line, i, j);
        // Insert new word
        strcpy(stringA, elementName);
        strcat(stringA, " ");
        insertStr(stringB, line, stringA, i);
        strcpy(line, stringB);
    }

#pragma endregion

#pragma region-- -- -(4) All instance of the string 'renameToListName' functions &Types-- -- -

    // Functions must be renamed first because of the extra "_"
    while (1)
    {
        strcpy(stringA, "renameToListName_");
        i = find_FirstSubstr_InStr(line, stringA);

        if (i == -1)
            break;

        j = strlen(stringA);
        // Remove word
        removeString(line, i, j);
        // Insert new word
        strcpy(stringA, listName);
        strcat(stringA, "_");
        insertStr(stringB, line, stringA, i);
        strcpy(line, stringB);
    }

    // Types
    while (1)
    {
        strcpy(stringA, "renameToListName");
        i = find_FirstSubstr_InStr(line, stringA);

        if (i == -1)
            break;

        j = strlen(stringA);
        // Remove word
        removeString(line, i, j);
        // Insert new word
        strcpy(stringA, listName);
        insertStr(stringB, line, stringA, i);
        strcpy(line, stringB);
    }

#pragma endregion

#pragma region-- -- -(5) Write the 'if' statements for the find functions-- -- -

    if (isDoneWritingFindFunc < 2)
    {
        strcpy(stringA, "findFunctionCondition"); // This string won't appear twice in one line
        i = find_FirstSubstr_InStr(line, stringA);

        if (i != -1)
        {
            isDoneWritingFindFunc++;

            j = strlen(stringA);
            // Remove word
            removeString(line, i, j);

            if (elmtMemberSize == 0) // Element is just a basic data type,
            {
                if (strcmp(elementName, "char *") == 0)
                    strcpy(stringA, "(strcmp(pList->pArray[i],target) == 0)");
                else
                    strcpy(stringA, "pList->pArray[i] == target"); // This will form the comparison of 'pList->pArray[i] == target'
                insertStr(stringB, line, stringA, i);
                strcpy(line, stringB);
            }
            else
            {
                clearCharArray(stringA);

                for (j = 0; j < elmtMemberSize; j++)
                {
                    if (strcmp(elementMemberData[j].type, "char *") == 0)
                    {
                        strcat(stringA, "(strcmp(pList->pArray[i].");
                        strcat(stringA, elementMemberData[j].variableName);
                        strcat(stringA, ",");
                        strcat(stringA, "target.");
                        strcat(stringA, elementMemberData[j].variableName);
                        strcat(stringA, ") == 0)");
                    }
                    else
                    {
                        strcat(stringA, "pList->pArray[i].");
                        strcat(stringA, elementMemberData[j].variableName);
                        strcat(stringA, "== target.");
                        strcat(stringA, elementMemberData[j].variableName);
                    }

                    if (j != elmtMemberSize - 1) // If this is not the last loop,
                    {
                        strcat(stringA, " && ");
                        // printf("%s\n", stringA);
                    }
                }

                insertStr(stringB, line, stringA, i);
                strcpy(line, stringB);
            }
        }
    }

#pragma endregion

#pragma region-- -- -(6) Write how the element is going to be initialised in renameToListName_CreateList()-- -- -

    do
    {
#pragma region _____ Checks _____
        if (isDoneAssigningDefaultVal)
            break;

        strcpy(stringB, "assignDefaultValue");
        k = find_FirstSubstr_InStr(line, stringB);

        if (k == -1)
            break;

        isDoneAssigningDefaultVal = true;
        removeString(line, k, strlen(stringB)); // Remove assignUserInput
        clearCharArray(stringB);
        clearCharArray(stringA);

        // Determine whether elmt type is a struct or not
        if (elmtMemberSize <= 0)
        {
            strcat(stringA, "pList->pArray[size]");
            strcat(stringA, " = ");
            strcat(stringA, defaultType_ValueName);
            strcat(stringA, ";\n");
            insertStr(stringB, line, stringA, k);
            strcpy(line, stringB);
            break;
        }

#pragma endregion

        for (i = 0; i < elmtMemberSize; i++)
        {
            boolA = false;
            for (j = 0; j < TYPELENGTH; j++)
            {
                if (boolA)
                    continue;
                if (find_FirstSubstr_InStr(elementMemberData[i].type, TYPE_DECLARATION[j]) == -1)
                    continue;

                boolA = true;
                switch (j)
                {
                case STRUCT:
                    printf("Sorry, we don't do nested struct initialization here. You'll have to initialize the struct yourself in the CreateList function\n");
                    break;
                case POINTER:
                    // Add allocate space line
                    strcat(stringA, "\t\tpList->pArray[size].");
                    strcat(stringA, elementMemberData[i].variableName);
                    strcat(stringA, " = (");
                    strcat(stringA, elementMemberData[i].type);
                    strcat(stringA, ")malloc(sizeof(");
                    strcat(stringA, elementMemberData[i].type);
                    strcat(stringA, "));\n");

                    // Add assign default value line
                    strcat(stringA, "\t\tpList->pArray[size].");
                    strcat(stringA, elementMemberData[i].variableName);
                    strcat(stringA, " = ");
                    strcat(stringA, defaultType_ValueName);
                    strcat(stringA, ".");
                    strcat(stringA, elementMemberData[i].variableName);
                    strcat(stringA, ";\n");
                    break;

                default: // ONLY FOR INT, FLOAT, BOOL TYPES
                    // Add assign default value line
                    strcat(stringA, "\t\tpList->pArray[size].");
                    strcat(stringA, elementMemberData[i].variableName);
                    strcat(stringA, " = ");
                    strcat(stringA, defaultType_ValueName);
                    strcat(stringA, ".");
                    strcat(stringA, elementMemberData[i].variableName);
                    strcat(stringA, ";\n");
                    break;
                }
            }
        }

        insertStr(stringB, line, stringA, k);
        strcpy(line, stringB);

        break;
    } while (1);

#pragma endregion

#pragma region-- -- -(7) Write the 'if' and 'output' statements to check if an element is considered 'empty' in the renameToListName_Print()-- -- -

#pragma region ~~~~~~~~~If Statements ~~~~~~~~~~~~~
    do
    {
#pragma region _____ Checks _____
        if (isDoneAssigningPrintCondition)
            break;

        strcpy(stringA, "printFunctionCondition"); // This string won't appear twice in one line
        i = find_FirstSubstr_InStr(line, stringA);

        if (i == -1)
            break;

        isDoneAssigningPrintCondition = true;
#pragma endregion

        j = strlen(stringA);
        // Remove word
        removeString(line, i, j);

#pragma region ____ If elmtMemberSize == 0 _____
        if (elmtMemberSize == 0) // Element is just a basic data type,
        {
            for (k = 0; k < TYPELENGTH; k++)
            {
                // Reverse element name to make sure that repeated data types like char * and char will get distinguished (because  '*' can then be found first instead of 'char')
                if (find_FirstSubstr_InStr(elementName, TYPE_DECLARATION[k]) == -1)
                    continue;

                switch (k)
                {
                case POINTER:
                    if (strcmp(elementName, "char *") == 0)
                    {
                        strcat(stringA, "(strcmp(");
                        strcat(stringA, "pList->pArray[i]");
                        strcat(stringA, ",");
                        strcat(stringA, defaultType_ValueName);
                        strcat(stringA, ".");
                        strcat(stringA, elementName);
                        strcat(stringA, ")==0)");
                    }
                    else
                        printf("Unable to write comparison for pointer variable: \'%s\' \n", elementName);
                    break;

                default:
                    // This will form the comparison of 'pList->pArray[i] == target'
                    strcpy(stringA, "pList->pArray[i] == ");
                    strcat(stringA, defaultType_ValueName);

                    break;
                }

                insertStr(stringB, line, stringA, i);
                strcpy(line, stringB);
                break; // exit for loop
            }

            break;
        }
#pragma endregion

#pragma region _____ If ElmtMemberSize> 0 _____
        clearCharArray(stringA);
        clearCharArray(stringB);

        for (j = 0; j < elmtMemberSize; j++)
        {
            boolA = false;
            for (k = 0; k < TYPELENGTH; k++)
            {
                if (boolA)
                    continue;
                if (find_FirstSubstr_InStr(elementMemberData[j].type, TYPE_DECLARATION[k]) == -1)
                    continue;

                boolA = true; // once type is matched, no need to keep looping with the same element member data
                switch (k)
                {
                case STRUCT:
                    printf("We dont support nested structs comparisons. You'll have to do the comparison code yourself here in ListPrint()\n");
                    break;

                case POINTER:
                    if (strcmp(elementMemberData[j].type, "char *") == 0)
                    {
                        strcat(stringA, "(strcmp(");
                        strcat(stringA, "pList->pArray[i].");
                        strcat(stringA, elementMemberData[j].variableName);
                        strcat(stringA, ",");
                        strcat(stringA, defaultType_ValueName);
                        strcat(stringA, ".");
                        strcat(stringA, elementMemberData[j].variableName);
                        strcat(stringA, ")==0)");
                    }
                    else
                        printf("Unable to write comparison for pointer variable: \'%s\' \n", elementMemberData[j].variableName);
                    break;

                default:
                    strcat(stringA, "pList->pArray[i].");
                    strcat(stringA, elementMemberData[j].variableName);
                    strcat(stringA, " == ");
                    strcat(stringA, defaultType_ValueName);
                    strcat(stringA, ".");
                    strcat(stringA, elementMemberData[j].variableName);
                    break;
                }

                if (j != elmtMemberSize - 1) // If this is not the last loop,
                {
                    strcat(stringA, " && ");
                    // printf("%s\n", stringA);
                }
            }
        }

        insertStr(stringB, line, stringA, i);
        strcpy(line, stringB);

#pragma endregion

        break;
    } while (1);
#pragma endregion

#pragma region ~~~~~~~~~Output Statements ~~~~~~~~~~~
    do
    {
#pragma region _____ Checks _____
        if (isDoneAssigningPrintOutput)
            break;

        strcpy(stringA, "printFunctionOutput"); // This string won't appear twice in one line
        i = find_FirstSubstr_InStr(line, stringA);

        if (i == -1)
            break;

        isDoneAssigningPrintOutput = true;
#pragma endregion

        j = strlen(stringA);
        // Remove word
        removeString(line, i, j);

#pragma region ____ If elmtMemberSize == 0 _____
        if (elmtMemberSize == 0) // Element is just a basic data type,
        {
            // This will form the comparison of 'pList->pArray[i] == target'
            strcpy(stringA, "printf(\"%d) ");

            for (k = 0; k < TYPELENGTH; k++)
            {
                if (find_FirstSubstr_InStr(elementName, TYPE_DECLARATION[k]) == -1)
                    continue;

                switch (k)
                {
                case STRUCT:
                    printf("It is impossible for code to run here. Something must be wrong!\n");
                    break;

                case POINTER:
                    if (strcmp(elementName, "char *") == 0)
                        strcat(stringA, "Value: %s\\n\", i, pList->pArray[i]);");
                    else
                    {
                        strcat(stringA, "Unable to print output for the variable \'");
                        strcat(stringA, elementName);
                        strcat(stringA, "\'\n");
                    }
                    break;

                default:
                    writeCode_printOutPut_ConcatForBasicCase(stringA, elementName, k);
                    break;
                }

                insertStr(stringB, line, stringA, i);
                strcpy(line, stringB);
                break;
            }
        }
#pragma endregion

#pragma region _____ If ElmtMemberSize> 0 _____
        clearCharArray(stringA);
        clearCharArray(stringB);

        strcpy(stringA, "printf(\"Element %d\\n\",i);\n");

        for (j = 0; j < elmtMemberSize; j++)
        {
            boolA = false;
            for (k = 0; k < TYPELENGTH; k++)
            {
                if (boolA)
                    continue;
                if (find_FirstSubstr_InStr(elementMemberData[j].type, TYPE_DECLARATION[k]) == -1)
                    continue;

                boolA = true;
                switch (k)
                {
                case STRUCT:
                    printf("We dont support nested structs print output. You'll have to do the comparison code yourself here in ListPrint()\n");
                    break;

                case POINTER:
                    if (strcmp(elementMemberData[j].type, "char *") == 0)
                    {
                        strcat(stringA, "printf(\"");
                        strcat(stringA, elementMemberData[j].variableName);
                        strcat(stringA, ": \'");
                        strcat(stringA, "%s");
                        strcat(stringA, "\' \\n\",pList->pArray[i]."); // closing inverted comma
                        strcat(stringA, elementMemberData[j].variableName);
                        strcat(stringA, ");\n");
                    }
                    else
                    {
                        strcat(stringA, "Unable to print output for the variable \'");
                        strcat(stringA, elementMemberData[j].variableName);
                        strcat(stringA, "\'\n");
                    }

                    break;

                default:
                    writeCode_printOutPut_ConcatForStructCase(stringA, elementMemberData[j].variableName, k);
                    break;
                }
            }
        }

        insertStr(stringB, line, stringA, i);
        strcpy(line, stringB);

#pragma endregion

        break;
    } while (1);

#pragma endregion

#pragma endregion

    return line;
}

void writeCode_printOutPut_ConcatForBasicCase(char *destination, char *variableName, int type)
{
    char a[300] = "";

    switch (type)
    {
    case INT:
        strcat(a, "Value: %d\\n\", i, pList->pArray[i]);");
        break;
    case FLOAT:
        strcat(a, "Value: %f\\n\", i, pList->pArray[i]);");
        break;
    case CHAR:
        strcat(a, "Value: %c\\n\", i, pList->pArray[i]);");
        break;
    case DOUBLE:
        strcat(a, "Value: %lf\\n\", i, pList->pArray[i]);");
        break;
    case LONG:
        strcat(a, "Value: %ld\\n\", i, pList->pArray[i]);");
        break;

    default:
        strcat(a, "Unable to print output for the variable \'");
        strcat(a, elementName);
        strcat(a, "\'\n");
        return;
    }

    strcat(destination, a);
}
void writeCode_printOutPut_ConcatForStructCase(char *destination, char *variableName, int type)
{
    char a[300] = "";
    strcat(a, "printf(\"");
    strcat(a, variableName);
    strcat(a, ": \'");

    switch (type)
    {
    case INT:
        strcat(a, "%d");
        break;
    case FLOAT:
        strcat(a, "%f");
        break;
    case CHAR:
        strcat(a, "%c");
        break;
    case DOUBLE:
        strcat(a, "%lf");
        break;
    case LONG:
        strcat(a, "%ld");
        break;

    default:
        strcpy(a, "Unable to print output for the variable \'");
        strcat(a, variableName);
        strcat(a, "\'\n");
        strcat(destination, a);
        return;
    }

    strcat(a, "\' \\n\",pList->pArray[i]."); // closing inverted comma
    strcat(a, variableName);
    strcat(a, ");\n");

    strcat(destination, a);
}