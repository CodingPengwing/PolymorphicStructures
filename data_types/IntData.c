
#include "IntData.h"


IntData_t *
intData_Create(int x)
{
    IntData_t *data = (IntData_t *) malloc(sizeof(IntData_t));
    data->x = x;
    return data;
}

void
intData_Print(IntData_t *data)
{
    printf("%d", data->x);
}

int
intData_Compare(IntData_t *data1, IntData_t *data2)
{
    int d1 = data1->x, d2 = data2->x;
    if (d1 < d2) 
        return -1;
    if (d1 > d2) 
        return +1;
    return 0;
}

void
intData_Free(IntData_t *data)
{
    free(data);
}
