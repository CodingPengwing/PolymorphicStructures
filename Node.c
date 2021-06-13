
#include "Node.h"


void
node_Print(Node_t *node)
{
    node->interface->Print(node->data);
}

int
node_Compare(Node_t *node1, Node_t *node2)
{
    if (node1->interface->Compare != node2->interface->Compare)
    {
        fprintf(stderr, "Error: node_Compare() cannot compare different data types");
        exit(EXIT_FAILURE);
    }
    return node1->interface->Compare(node1->data, node2->data);
}

int
node_p_Compare(Node_t **node1, Node_t **node2)
{
    return node_Compare(*node1, *node2);
}

void
node_Free(Node_t *node)
{
    if (node->data) 
    {
        node->interface->Free(node->data);
        node->data = NULL;
    }
    free(node);
}

Node_t *
node_Create(void *data, NodeInterface_t *interface)
{
    Node_t *node = (Node_t *) malloc(sizeof(Node_t));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->interface = interface;
    return node;
}

void 
node_Swap_Data(Node_t *node_1, Node_t *node_2)
{
    void *tmp_data = node_1->data;
    node_1->data = node_2->data;
    node_2->data = tmp_data;
}
