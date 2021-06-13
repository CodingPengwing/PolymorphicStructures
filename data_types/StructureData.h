
#include "../Node.h"
#include "../Structure.h"
#include "../structure_types/Array.h"

#ifndef STRUCTURED_DATA_H
#define STRUCTURED_DATA_H

typedef struct structure_data {
    Structure_t *structure;
} StructureData_t;

StructureData_t *
structureData_Create(Structure_t *structure);

void
structureData_Print(StructureData_t *data);

void
structureData_Sort(StructureData_t *data);

void
structureData_Free(StructureData_t *data);

static NodeInterface_t *NodeInterface_StructureData = &(NodeInterface_t) {
    .Print = (void (*)(void *)) structureData_Print,
    .Free = (void (*)(void *)) structureData_Free
};

#endif // STRUCTURED_DATA_H
