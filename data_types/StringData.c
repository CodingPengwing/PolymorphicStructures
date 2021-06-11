
#include "StringData.h"

StringData_t *
stringData_Create(char *string)
{
    if (!string) exit_with_error("Error in stringData_Create(): cannot initialise Data for NULL pointer.");
    int len = strlen(string);
    StringData_t *data = (StringData_t *) malloc(sizeof(StringData_t));
    data->string = (char *)malloc(len * sizeof(*data->string));
    strncpy(data->string, string, len);
    return data;
}

void
stringData_Print(StringData_t *data)
{
    printf("%s", data->string);
}

int
stringData_Compare(StringData_t *data1, StringData_t *data2)
{
    int len1 = strlen(data1->string);
    int len2 = strlen(data2->string);
    if (len1 == 0 && len2 != 0) 
        return -1;
    if (len1 != 0 && len2 == 0) 
        return +1;
    
    int n = (len1 < len2) ? len1 : len2;
    return strncmp(data1->string, data2->string, n);
}

void
stringData_Free(StringData_t *data)
{
    if (data->string) 
    {
        free(data->string);
        data->string = NULL;
    }
    free(data);
}
