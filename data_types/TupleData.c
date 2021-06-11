
#include "TupleData.h"

TupleData_t *
tupleData_Create(int x, char *string)
{
    if (!string) exit_with_error("Error: tupleData_Create() was given NULL");

    TupleData_t *data = (TupleData_t *) malloc(sizeof(TupleData_t));
    assert(data);
    data->x = x;
    if (string) 
    {
        data->string = string_Create(strlen(string) + 1);
        strncpy(data->string, string, strlen(string));
    } 
    else data->string = NULL;
    return data;
}

void
tupleData_Print(TupleData_t *data)
{
    printf("(%d, %s)", data->x, data->string);
}

int
tupleData_Compare(TupleData_t *data1, TupleData_t *data2)
{
    int d1 = data1->x, d2 = data2->x;
    if (d1 < d2) return -1;
    if (d1 > d2) return +1;
    
    // for use in strncmp() if new compare rules apply
    // int len1 = strlen(data1->string), len2 = strlen(data2->string);
    // int n = (len1 < len2) ? len1 : len2;
    return strcmp(data1->string, data2->string);
}

void
tupleData_Free(TupleData_t *data)
{
    if (data->string) 
    {
        free(data->string);
        data->string = NULL;
    }
    free(data);
}
