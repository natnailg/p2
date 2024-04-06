//
// Created by Natnail on 3/30/2024.
//

#ifndef P2_TREENODE_H
#define P2_TREENODE_H

#include "BuildTree.h"
#define MAX_INSTANCE_TOKEN 256

typedef struct node_t{

    char Label; // the value of the node (label of the functions)
    struct node_t* left; // pointer to the left node
    struct node_t* right; // pointer to the right
    struct node_t* center;
    struct node_t* far_right;
    char token_instance[MAX_INSTANCE_TOKEN];  //printing token instance value
    char* token_id;
}node_t;



#endif //P2_TREENODE_H
