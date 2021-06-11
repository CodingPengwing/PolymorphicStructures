
#include <string.h>

#include "../util.h"
#include "../Node.h"

#ifndef TUPLE_DATA_H
#define TUPLE_DATA_H

typedef struct {
    int x;
    char *string;
} TupleData_t;

TupleData_t *
tupleData_Create(int x, char *string);

void
tupleData_Print(TupleData_t *data);

int
tupleData_Compare(TupleData_t *data1, TupleData_t *data2);

void
tupleData_Free(TupleData_t *data);

static NodeInterface_t *TupleData_as_Node = &(NodeInterface_t) 
{
    .Print = (void (*)(void *)) tupleData_Print,
    .Compare = (int (*)(void *, void *)) tupleData_Compare,
    .Free = (void (*)(void*)) tupleData_Free
};

#endif // TUPLE_DATA_H
