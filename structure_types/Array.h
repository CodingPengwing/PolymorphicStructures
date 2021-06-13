
#include <stdio.h>
#include <stdlib.h>

#include "../Node.h"
#include "../util.h"

#ifndef ARRAY_H
#define ARRAY_H

typedef Node_t** NodeArray;

// This contains an array of Nodes. The array allows gaps (NULL)
// which is why we have n_elements.
typedef struct array {
    NodeArray nodeArray;
    size_t size;
    size_t n_elements;
} Array_t;


Array_t *
array_Create(size_t array_size);

void
array_Print(Array_t *array);

// Sort the Array. Warning: This would only work if all Nodes inside
// the Array contain the same type of Data.
void
array_Sort(Array_t *array);

void
array_Free(Array_t *array);

static NodeInterface_t *NodeInterface_Array = &(NodeInterface_t) {
    .Print = (void (*)(void *)) array_Print,
    .Sort = (void (*)(void *)) array_Sort,
    .Free = (void (*)(void *)) array_Free
};

void
array_Insert(Array_t *array, Node_t *node, size_t index);

void
array_InsertNext(Array_t *array, Node_t *node);

#endif
