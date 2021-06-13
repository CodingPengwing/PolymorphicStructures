/*  An implementation of a Linked List structure.
    It contains Nodes which contains Data
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "../Node.h"
#include "../Structure.h"
#include "../util.h"

#ifndef LIST_H
#define LIST_H

typedef struct linked_list {
    Node_t *top;
    Node_t *bottom;
    size_t size;
} List_t;

// Create a new empty List and return a pointer to it
List_t *
list_Create();

// Print the List - [x_1, x_2, ..., x_n]
void 
list_Print(List_t *list);
// Recalculate the number of elements in a List
int 
list_Size(List_t *list);

// Add an element to the top of a List
void 
list_InsertTop(List_t *list, Node_t *node);

// Add an element to the bottom of a List
void 
list_InsertBottom(List_t *list, Node_t *node);

// Remove and return the top element from a List
Node_t *
list_RemoveTop(List_t *list);

// Remove and return the bottom element from a List
Node_t *
list_RemoveBottom(List_t *list);

// Remove specified Node from the List
Node_t *
list_RemoveCustom(List_t *list, Node_t *node);

// Free the memory associated with a List
void 
list_Free(List_t *list);

// Reverse the List
void 
list_Reverse(List_t *list);

// Move all values that are bigger than the pivot to the bottom of the List
void 
list_Sift(List_t *list, void *pivot);

// This is a O(n^2) implementation of sorting, the code is quite short but the
// computation are quite taxing. It might be better to just copy all the elements 
// into an array, sort them using the standard qsort() function, and then copy back
// into the List. The user can explore the Array package to see how an array of Data 
// can be easily created and sorted.
void
list_Sort(List_t *list);

// Check to see if List contains this Data
bool 
list_Contains(List_t *list, Node_t *node);


static StructureInterface_t *StructureInterface_List = &(StructureInterface_t) {
    .Print = (void (*)(void *)) list_Print,
    .Sort = (void (*)(void *)) list_Sort,
    .Free = (void (*)(void *)) list_Free
};

#endif 
