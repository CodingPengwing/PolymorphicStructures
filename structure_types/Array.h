
#include <stdio.h>
#include <stdlib.h>

#include "../Node.h"
#include "../Structure.h"
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

int
node_Sort(Node_t **node1, Node_t **node2);

void
array_Sort(Array_t *array);

void
array_Free(Array_t *array);

static StructureInterface_t *Array_as_Structure = &(StructureInterface_t) {
    .Print = (void (*)(void *)) array_Print,
    .Sort = (void (*)(void *)) array_Sort,
    .Free = (void (*)(void *)) array_Free
};

void
array_Insert(Array_t *array, Node_t *node, size_t index);

void
array_InsertNext(Array_t *array, Node_t *node);

#endif
