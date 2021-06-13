
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifndef NODE_H
#define NODE_H

//  Creating a virtual table for nodes
typedef struct node_interface {
    void (*Print)(void *data);
    int (*Compare)(void *data1, void *data2);
    void (*Sort)(void *data);
    void (*Free)(void *data);
} NodeInterface_t;

typedef struct node Node_t;
struct node {
    void *data;
    const NodeInterface_t *interface;
    // Left/Right pointer used for list/tree structures
    Node_t *left;
    Node_t *right;   
};


void
node_Print(Node_t *node);

int
node_Compare(Node_t *node1, Node_t *node2);

void
node_Free(Node_t *node);

Node_t *
node_Create(void *data, NodeInterface_t *interface);

void 
node_Swap_Data(Node_t *node1, Node_t *node2);

#endif
