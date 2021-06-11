
#include "FloatData.h"

FloatData_t *
floatData_Create(float x)
{
    FloatData_t *data = (FloatData_t *) malloc(sizeof(FloatData_t));
    data->x = x;
    return data;
}

void
floatData_Print(FloatData_t *data)
{
    printf("%f", data->x);
}

int
floatData_Compare(FloatData_t *data1, FloatData_t *data2)
{
    float d1 = data1->x, d2 = data2->x;
    if (d1 < d2) 
        return -1;
    if (d1 > d2) 
        return +1;
    return 0;
}

void
floatData_Free(FloatData_t *data)
{
    free(data);
}
