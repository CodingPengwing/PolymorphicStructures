
#include "../Node.h"

#ifndef FLOATDATA_H
#define FLOATDATA_H

typedef struct {
    float x;
} FloatData_t;

FloatData_t *
floatData_Create(float x);

void
floatData_Print(FloatData_t *data);

int
floatData_Compare(FloatData_t *data1, FloatData_t *data2);

void
floatData_Free(FloatData_t *data);

static NodeInterface_t *NodeInterface_FloatData = &(NodeInterface_t) 
{
    .Print = (void (*)(void *)) floatData_Print,
    .Compare = (int (*)(void *, void *)) floatData_Compare,
    .Free = (void (*)(void*)) floatData_Free
};

#endif
