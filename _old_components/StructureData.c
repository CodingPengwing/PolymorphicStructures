
#include "StructureData.h"

StructureData_t *
structureData_Create(Structure_t *structure)
{
    StructureData_t *data = (StructureData_t *) malloc(sizeof(*data));
    if (structure) data->structure = structure;
    return data;
}

void
structureData_Print(StructureData_t *data)
{
    structure_Print(data->structure);
}

void
structureData_Sort(StructureData_t *data)
{
    structure_Sort(data->structure);
}

void
structureData_Free(StructureData_t *data)
{
    structure_Free(data->structure);
    data->structure = NULL;
    free(data);
}
