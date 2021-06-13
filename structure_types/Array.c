
#include "Array.h"

void
array_Print(Array_t *array)
{
    NodeArray nodeArray = array->nodeArray;

    printf("[");
    for (size_t i = 0; i < array->size; i++)
    {
        if (nodeArray[i]) 
            node_Print(nodeArray[i]);
        else 
            printf("_");

        if (i != array->size - 1) 
            printf(", ");
    }
    printf("]");
}

// Sort the Array. Warning: This would only work if all Nodes inside
// the Array contain the same type of Data.
void
array_Sort(Array_t *array)
{
    NodeArray nodeArray = array->nodeArray;
    size_t array_size = array->size;

    qsort(nodeArray, array_size, sizeof(*nodeArray), (int (*)(const void *, const void *))node_p_Compare);
}

void
array_Free(Array_t *array)
{
    NodeArray nodeArray = array->nodeArray;

    for (size_t i = 0; i < array->size; i++)
    {
        if (nodeArray[i]) {
            node_Free(nodeArray[i]);
            nodeArray[i] = NULL;
        }
    }
    free(nodeArray);
    array->nodeArray = NULL;
    free(array);
}

Array_t *
array_Create(size_t array_size)
{
    Array_t *array = (Array_t *) malloc(sizeof(Array_t));
    assert(array);
    array->nodeArray = (NodeArray) malloc(sizeof(*array->nodeArray)*array_size);
    assert(array->nodeArray);
    // Initialise all indices to NULL
    for (size_t i=0; i<array_size; i++) array->nodeArray[i] = NULL;
    array->size = array_size;
    array->n_elements = 0;
    return array;
}

void
array_Insert(Array_t *array, Node_t *node, size_t index)
{
    if (!check_index(array->size, index)) exit_with_error("Error: array_Insert() index out of range");

    if (array->nodeArray[index]) 
    {
        node_Free(array->nodeArray[index]);
        array->nodeArray[index] = NULL;
    }

    array->nodeArray[index] = node;
    array->n_elements++;
}

void
array_InsertNext(Array_t *array, Node_t *node)
{
    if (array->n_elements >= array->size) exit_with_error("Error in array_InsertNext(): array is full.");
    for (size_t i = 0; i < array->size; i++)
    {
        if (!array->nodeArray[i])
        {
            array->nodeArray[i] = node;
            return;
        }
    }
}
