#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#pragma region ===== Definitions =====
// typedef struct renameToElmtName
// {
//     int value;
//     char *name;
// } renameToElmtName;

typedef struct renameToListName
{
    // The current number of occupied slots in the array
    int count;
    // The actual size of the array (count + buffer size)
    int capacity;
    // The pointer of the the array
    renameToElmtName *pArray;
} renameToListName;
#pragma endregion

#pragma region ===== Global Vars =====
// const int DEFAULT_BUFFER_SIZE = 4;
const renameToElmtName DEFAULT_TYPE_VALUE = ;
#pragma endregion

#pragma region ===== Function Prototypes =====

#pragma region-- -- -Core Functions-- -- -
// Returns a reference to the head/root element that was the very first element created.
static renameToListName *renameToListName_CreateList(int size);
// Prints all the elements in the list
void renameToListName_Print(renameToListName *pList);
// Gets an element's pointer from the list at a specific index of the list
renameToElmtName *renameToListName_GetElmtPointer(renameToListName *pList, int index);

// Gets an element as a value from the list at a specific index of the list
renameToElmtName renameToListName_GetElmtValue(renameToListName *pList, int index);
#pragma endregion

#pragma region-- -- -Find Functions-- -- -
// Returns true if a value is found in the list.
bool renameToListName_Contain(renameToListName *pList, renameToElmtName target);
// Returns the index of the value found in the list. If no value is not found, -1 is returned.
int renameToListName_IndexOf(renameToListName *pList, renameToElmtName target);
#pragma endregion

#pragma region-- -- -Add Functions-- -- -
// Adds a element to the end of the list
void renameToListName_Add(renameToListName *pList, renameToElmtName toAdd);
// Checks if the count of the list has reached its capacity and resizes the internal array if needed.
void renameToListName_assertCapacity(renameToListName *pList);

void renameToListName_Insert(renameToListName *pList, renameToElmtName toAdd, int index);
#pragma endregion

#pragma region-- -- -Remove Functions-- -- -
// Removes a element from the list at a specific index of the list.
void renameToListName_RemoveAt(renameToListName *pList, int index);

// Removes a element from the list at a specific index of the list but messes up the order of the list. Is faster than RemoveAt().
void renameToListName_DirtyRemove(renameToListName *pList, int index);

// Clears the entire list of its elements
void renameToListName_Clear(renameToListName *pList);

// Optimizes the memory the list occupies by assigning memory up to the countth element
void renameToListName_TrimExcess(renameToListName *pList);
#pragma endregion

#pragma endregion

#pragma region ===== General Functions =====
static renameToListName *renameToListName_CreateList(int size)
{
    renameToListName *pList = (renameToListName *)malloc(sizeof(renameToListName));
    pList->capacity = size;
    pList->count = 0;
    pList->pArray = (renameToElmtName *)malloc(pList->capacity * sizeof(renameToElmtName));

    for (size = 0; size < pList->count; size++)
    {
        assignDefaultValue
        // pList->pArray[size].name = (char *)malloc(sizeof(char *));
        // pList->pArray[size].name = DEFAULT_TYPE_VALUE.name;
        // pList->pArray[size].value = DEFAULT_TYPE_VALUE.value;
    }

    return pList;
}

void renameToListName_Print(renameToListName *pList)
{
    int i;
    printf("===== Print List ===== \n Count: %d Capacity: %d \n", pList->capacity, pList->count);
    printf("--- Count --- \n");
    for (i = 0; i < pList->count; i++)
    {
        // if (pList->pArray[i].name == DEFAULT_TYPE_VALUE.name && pList->pArray[i].value == DEFAULT_TYPE_VALUE.value)
        if (printFunctionCondition)
            continue;
        else
        {
            printFunctionOutput
            // printf("%d) %d \n", i, pList->pArray[i].value);
            // printf("%s \n", pList->pArray[i].name);
        }
    }

    printf("--- Capacity --- \n");
    for (i = pList->count; i < pList->capacity; i++)
        printf("%d) EMPTY \n", i);
}

renameToElmtName *renameToListName_GetElmtPointer(renameToListName *pList, int index)
{
    if (index >= pList->count)
    {
        printf("Trying to get index of %d  has failed because index exceeded the count of the list.", index);
        return NULL;
    }
    return &pList->pArray[index];
}

renameToElmtName renameToListName_GetElmtValue(renameToListName *pList, int index)
{
    if (index >= pList->count)
    {
        printf("Trying to get index of %d  has failed because index exceeded the count of the list.", index);
        return DEFAULT_TYPE_VALUE;
    }
    return pList->pArray[index];
}
#pragma endregion

#pragma region ===== Find Functions =====
bool renameToListName_Contain(renameToListName *pList, renameToElmtName target)
{
    for (int i = 0; i < pList->count; i++)
    {
        // if (pList->pArray[i].name == target.name && pList->pArray[i].value == target.value)
        if (findFunctionCondition)
        {
            return true;
        }
    }
    return false;
}

int renameToListName_IndexOf(renameToListName *pList, renameToElmtName target)
{
    for (int i = 0; i < pList->count; i++)
    {
        // if (pList->pArray[i].name == target.name && pList->pArray[i].value == target.value)
        if (findFunctionCondition)
        {
            return i;
        }
    }
    return -1;
}
#pragma endregion

#pragma region ===== Add Functions =====
void renameToListName_Add(renameToListName *pList, renameToElmtName toAdd)
{
    renameToListName_assertCapacity(pList);
    pList->pArray[pList->count] = toAdd; // Add new elmt to the array
    pList->count++;                      // Update count
}

void renameToListName_Insert(renameToListName *pList, renameToElmtName toAdd, int index)
{
    // Check if index exceeds the count of list (that means element doesnt get added into the buffer is the default buffer size = 1)
    if (index > pList->count)
    {
        printf("Unable to insert element! The index you want to insert the element exceeds the count of the list!\n");
        return;
    }

    // If index the same as the count, that means the element wants to occupy the extra slot in the buffersize. So we just append the element to the end of the array
    if (index == pList->count)
    {
        renameToListName_Add(pList, toAdd);
        return;
    }

    renameToListName_assertCapacity(pList);
    // Else, element wants to be inserted in between existing elmts and make life difficult
    //  Index: 1
    //[0]   [1]    [2]      [3]
    // 21 -> 56 -> 900 -> EMPTY
    //      ^
    //      9

    renameToElmtName prevElmt = pList->pArray[index];
    pList->pArray[index] = toAdd; // Assign new element

    int i, correctindex;
    for (i = 1; i <= pList->count - index; i++)
    {
        correctindex = index + i;
        toAdd = pList->pArray[correctindex];    // Store original element
        pList->pArray[correctindex] = prevElmt; // Set the array element the previous element
        prevElmt = toAdd;                       // Set new previous element
    }

    pList->count++;
}

void renameToListName_assertCapacity(renameToListName *pList)
{
    if (pList->count == pList->capacity)
    {
        pList->capacity = pList->capacity == 0 ? 4 : pList->count * 2; // Update capacity with DEFAULT_BUFFER_SIZE

        renameToElmtName *pNewArray = (renameToElmtName *)malloc(pList->capacity * sizeof(renameToElmtName)); // Create new array
        for (size_t i = 0; i < pList->count; i++)                                                             // Copy old array data to new array
            pNewArray[i] = pList->pArray[i];

        free(pList->pArray);       // Free old array
        pList->pArray = pNewArray; // Assign new array
    }
}

#pragma endregion

#pragma region ===== Remove Functions =====

void renameToListName_RemoveAt(renameToListName *pList, int index)
{
    // Check if index exceeds the count of list (that means element doesnt get added into the buffer is the default buffer size = 1)
    if (index > pList->count)
    {
        printf("Unable to remove at index %d! The index you want to remove exceeds the count of the list!\n", index);
        return;
    }

    // Else, element wants to be removed in between existing elmts and make life difficult
    //  Index: 1
    //[0]   [1]    [2]      [3]
    // 21 -> 56 -> 900 -> EMPTY
    //      ^
    //      REMOVE

    int i, nextIndex;
    for (i = 1; i < pList->count - index; i++)
    {
        nextIndex = index + i; // This index represents the element that is infront of the current element that is getting replaced.
        pList->pArray[nextIndex - 1] = pList->pArray[nextIndex];
    }

    pList->count--;
}

void renameToListName_DirtyRemove(renameToListName *pList, int index)
{
    // Check if index exceeds the count of list (that means element doesnt get added into the buffer is the default buffer size = 1)
    if (index > pList->count)
    {
        printf("Unable to remove at index %d! The index you want to remove exceeds the count of the list!\n", index);
        return;
    }

    pList->pArray[index] = pList->pArray[pList->count - 1];
    renameToListName_RemoveAt(pList, pList->count - 1);
}

void renameToListName_Clear(renameToListName *pList)
{
    free(pList);
    pList = renameToListName_CreateList(0);
}

void renameToListName_TrimExcess(renameToListName *pList)
{
    if (pList->count != pList->capacity)
    {
        pList->capacity = pList->count; // Update capacity

        renameToElmtName *pNewArray = (renameToElmtName *)malloc(pList->capacity * sizeof(renameToElmtName)); // Create new array
        for (size_t i = 0; i < pList->count; i++)                                                             // Copy old array data to new array
            pNewArray[i] = pList->pArray[i];

        free(pList->pArray);       // Free old array
        pList->pArray = pNewArray; // Assign new array
    }
}

#pragma endregion