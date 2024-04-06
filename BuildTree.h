//
// Created by Natnail on 3/30/2024.
//

#ifndef P2_BUILDTREE_H
#define P2_BUILDTREE_H

#include "TreeNode.h"

struct node_t* createNode(char); // for creating a new node for tree, takes a value

void print_preorder_tree(node_t* root, int depth); //printing the tree pre-orde

void freeNode(node_t* node);

#endif //P2_BUILDTREE_H
