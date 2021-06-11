
#include <string.h>

#include "../Node.h"
#include "../util.h"

#ifndef STRINGDATA_H
#define STRINGDATA_H

typedef struct {
    char *string;
} StringData_t;

StringData_t *
stringData_Create(char *string);

void
stringData_Print(StringData_t *data);

int
stringData_Compare(StringData_t *data1, StringData_t *data2);

void
stringData_Free(StringData_t *data);

static NodeInterface_t *StringData_as_Node = &(NodeInterface_t) 
{
    .Print = (void (*)(void *)) stringData_Print,
    .Compare = (int (*)(void *, void *)) stringData_Compare,
    .Free = (void (*)(void*)) stringData_Free
};

#endif // STRINGDATA_H
