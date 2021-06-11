
#include "Structure.h"

void
structure_Print(Structure_t *structure)
{
    structure->interface->Print(structure->content);
}

void
structure_Sort(Structure_t *structure)
{
    structure->interface->Sort(structure->content);
}

void
structure_Free(Structure_t *structure)
{
    structure->interface->Free(structure->content);
    structure->content = NULL;
    free(structure);
}

Structure_t *
structure_Create(void *content, StructureInterface_t *interface)
{
    Structure_t *structure = (Structure_t *) malloc(sizeof(Structure_t));
    structure->content = content;
    structure->depth_level = 0;
    structure->interface = interface;
    return structure;
}
