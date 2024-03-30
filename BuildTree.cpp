//
// Created by Natnail on 3/30/2024.
//(TreeNode*)

#include <stdio.h>
#include <stdlib.h>

//#include "TreeNode.h"
#include "BuildTree.h"

//function to create a new node for the binary tree
struct node_t* createNode(char Label){
    //allocate memo for new node
    struct node_t* new_Node = (struct node_t*)malloc(sizeof(struct node_t));
    //check to see if mem allocation was successful
    if(new_Node == NULL){
        printf("Error, memory allocation!\n");
        return NULL;
    }
    if (new_Node != NULL) {
        //initalize node data
        new_Node->Label = Label;
        new_Node->left = NULL;
        new_Node->right = NULL;
    }
    //return the created node
    return new_Node;
}

// Function to print the abstract syntax tree (AST)
void printAST(node_t* root, int depth) {
    if (root == NULL) {
        return;
    }
    // Print the current node with appropriate indentation
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("%c\n", root->Label);

    // Recursively print the left subtree with increased depth
    printAST(root->left, depth + 1);
    // Recursively print the right subtree with increased depth
    printAST(root->right, depth + 1);
}















/*
//function to inset a node into the binary tree
struct node_t* insertNode(struct node_t* root, char value){
    //if the tree is empty, create a new node
    if (root == NULL) {
        return createNode(value);
    }

    // If the value is less than the root's data, insert into the left subtree
    if (value < root->Label) {
        root->left = insertNode(root->left, value);
    }
        // If the value is greater than the root's data, insert into the right subtree
    else if (value > root->Label) {
        root->right = insertNode(root->right, value);
    }

    // Return the modified root
    return root;
}
*/

