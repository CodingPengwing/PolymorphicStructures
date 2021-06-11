
#include "List.h"


// Create a new empty List and return a pointer to it
List_t *
list_Create() 
{
    List_t *list = (List_t *) malloc(sizeof(*list));
    assert(list);
    list->top = NULL;
    list->bottom = NULL;
    list->size = 0;
    return list;
}

// Print the List - [x_1, x_2, ..., x_n]
void 
list_Print(List_t *list) 
{
    Node_t *current = list->top;
    printf("[");
    while (current) 
    {
        node_Print(current);
        // Print a comma unless we just printed the final element
        if (current != list->bottom) 
            printf("->");
        current = current->right;
    }
    printf("]");
}

// Recalculate the number of elements in a List
int 
list_Size(List_t *list) 
{
    Node_t *current = list->top;
    int counter = 0;
    while (current) 
    {
        counter++;
        current = current->right;
    }
    list->size = counter;
    return list->size;
}

// Add an element to the top of a List
void 
list_InsertTop(List_t *list, Node_t *node) 
{
    if(list->size) 
    {
        node->right = list->top;
        list->top->left = node;
        list->top = node;
    } 
    else 
        list->top = list->bottom = node;

    list->size++;
}

// Add an element to the bottom of a List
void 
list_InsertBottom(List_t *list, Node_t *node) 
{
    if(list->size) 
    {
        node->left = list->bottom;
        list->bottom->right = node;
        list->bottom = node;
    } 
    else 
        list->top = list->bottom = node;

    list->size++;
}

// Remove and return the top element from a List
Node_t *
list_RemoveTop(List_t *list) 
{
    if (list->size == 0) 
        exit_with_error("can't remove from empty list");
    
    Node_t *old_top = list->top;

    if (list->size > 1)
    {
        list->top = list->top->right;
        list->top->left = NULL;
    }
    else 
        list->top = list->bottom = NULL;
    
    list->size--;
    return old_top;
}

// Remove and return the bottom element from a List
Node_t *
list_RemoveBottom(List_t *list) 
{
    if (list->size == 0) 
        exit_with_error("can't remove from empty list");
    
    Node_t *old_bottom = list->bottom;

    if (list->size > 1) 
    {
        list->bottom = list->bottom->left;
        list->bottom->right = NULL;
    }
    else 
        list->top = list->bottom = NULL;

    list->size--;
    return old_bottom;
}

// Remove specified Node from the List
Node_t *
list_RemoveCustom(List_t *list, Node_t *node) 
{
    if (list->size == 0) 
        exit_with_error("can't remove from empty list");
    
    // If Node is at the bottom or top of the List then  
    // use remove functions already provided
    if (!node->left) 
        return list_RemoveTop(list);
    if (!node->right) 
        return list_RemoveBottom(list);
    
    // Disconnect Node from List
    // Connect the corresponding adjacent Nodes together
    node->left->right = node->right;
    node->right->left = node->left;

    list->size--;
    return node;
}

// Free the memory associated with a List
void 
list_Free(List_t *list) 
{
    while(list->size) 
    {
        Node_t *node = list_RemoveTop(list);
        node_Free(node);
        *(&node) = NULL;
    }
    list->top = list->bottom = NULL;
    free(list);
}

// Reverse the List
void 
list_Reverse(List_t *list) 
{
    Node_t *curr_node = list->top;
    Node_t *tmp;

    if (list->size <= 1) 
        return;

    while (curr_node) 
    {   
        // Swap "right" and "left" pointers
        tmp = curr_node->right;
        curr_node->right = curr_node->left;
        curr_node->left = tmp;
        // Move to right Node in List, which is now "left" Node
        curr_node = curr_node->left;
    }
    // Swap top and bottom pointers
    tmp = list->top;
    list->top = list->bottom;
    list->bottom = tmp;
}

// Move all values that are bigger than the pivot to the bottom of the List
// pivot should be a Data_t
void 
list_Sift(List_t *list, void *pivot) 
{
    if (list->size <= 1) return;
    
    Node_t *curr = list->top;
    Node_t *swap;
    // Remove any Node with value > pivot, insert them at the 
    // bottom of tmp_list
    while (curr) 
    {
        if (curr->interface->Compare(curr->data, pivot) > 0) 
        {
            swap = curr->right;
            // try to find the next node that is <= pivot
            while (swap)
            {
                if (curr->interface->Compare(swap->data, pivot) <= 0) break;
                else swap = swap->right;
            }
            // if swap is NULL, there is no more shuffling to be done
            if (!swap) break;
            // else swap the data of the 2 nodes
            node_Swap_Data(curr, swap);
        } 
        curr = curr->right;
    }
}

// This is a O(n^2) implementation of sorting, the code is quite short but the
// computation are quite taxing. It might be better to just copy all the elements 
// into an array, sort them using the standard qsort() function, and then copy back
// into the List. The user can explore the Array package to see how an array of Data 
// can be easily created and sorted.
void
list_Sort(List_t *list)
{
    Node_t *current = list->top;
    while (current)
    {
        // Move all elements bigger than current Data to bottom of List
        list_Sift(list, current->data);
        current = current->right;
    }
}

// Check to see if List contains this Data
bool 
list_Contains(List_t *list, Node_t *node)
{
    Node_t *current = list->top;
    while (current)
    {
        if (node_Compare(current, node) == 0) 
            return true;
        current = current->right;
    }
    return false;
}

