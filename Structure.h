
#include "Node.h"

#include <stdio.h>
#include <stdlib.h>

#ifndef STRUCTURE_H
#define STRUCTURE_H


typedef struct structure_interface {
    void (*Print)(void * content);
    void (*Sort)(void * content);
    void (*Free)(void * content);
} StructureInterface_t;

typedef struct structure {
    void *content;
    int depth_level;
    const StructureInterface_t *interface;
} Structure_t;


void
structure_Print(Structure_t *structure);

void
structure_Sort(Structure_t *structure);

void
structure_Free(Structure_t *structure);

Structure_t *
structure_Create(void *content, StructureInterface_t *interface);

#endif
