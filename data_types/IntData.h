
#include "../Node.h"

#ifndef INTDATA_H
#define INTDATA_H

typedef struct {
    int x;
} IntData_t;

IntData_t *
intData_Create(int x);

void
intData_Print(IntData_t *data);

int
intData_Compare(IntData_t *data1, IntData_t *data2);

void
intData_Free(IntData_t *data);

static NodeInterface_t *NodeInterface_IntData = &(NodeInterface_t) 
{
    .Print = (void (*)(void *)) intData_Print,
    .Compare = (int (*)(void *, void *)) intData_Compare,
    .Free = (void (*)(void*)) intData_Free
};

#endif // INTDATA_H
