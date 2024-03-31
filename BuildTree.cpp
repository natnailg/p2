//
// Created by Natnail on 3/30/2024.
//(TreeNode*)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BuildTree.h"
#include "TreeNode.h"

//function to create a new node for the binary tree
node_t* createNode(char label){
    //allocate memo for new node
    node_t* new_Node = (struct node_t*)malloc(sizeof(struct node_t));
    //check to see if mem allocation was successful
    if(new_Node == NULL){
        printf("Error, memory allocation!\n");
        return NULL;
    }
    if (new_Node != NULL) {

        //initalize node data
        new_Node->Label = label;        // the functions
        new_Node->left = NULL;          //left child
        new_Node->center =NULL;         //some have three children
        new_Node->right = NULL;         //right child
        new_Node->far_right = NULL;     // far right child (fourth child)
        new_Node->token_instance[0] = '\0';        //token instances
    }
    //return the created node
    return new_Node;
}

// Function to print the abstract syntax tree (AST)
//void printAST(node_t* root, int depth) {
//    if (root == NULL) {
//      //  printf("Error root is Null in PrintAST\n");
//        return;
//    }
//    // Print the current node with appropriate indentation
//    for (int i = 0; i < depth; i++) {
//        printf("  ");
//    }
//    printf("%c\n", root->Label);
//
//    // Recursively print the left subtree with increased depth
//    printAST(root->left, depth + 1);
//    // Recursively print the right subtree with increased depth
//    printAST(root->right, depth + 1);
//}

void printAST(node_t* root, int depth) {
    if (root == NULL) {
        // printf("Error root is Null in PrintAST\n");
        return;
    }

    // Print the current node with appropriate indentation
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    // Skip printing nodes with label 'X'
    if (root->Label != ' ')
    {
        printf("%*c%c\n", depth*5, ' ', root->Label);
    }
    else{
        //printf("%c", root->Label);
        // Print token instance if it exists
        printf(" (%d, %s)\n", root->token_id, root->token_instance);

    }

    // Recursively print the left subtree with increased depth
    if(root->left != NULL){
    printAST(root->left, depth + 1);
    }

    // Recursively print the right subtree with increased depth
    if(root->right != NULL) {
        printAST(root->right, depth + 1);
    }
    if(root->center != NULL) {
        printAST(root->center, depth + 1);
    }
}



//void freeNode(node_t* node) {
//    if (node == NULL) {
//        return;
//    }
//    freeNode(node->left);
//    freeNode(node->right);
//    free(node);
//}
void freeNode(node_t* node) {
    if (node == NULL) {
        return;
    }
    freeNode(node->left);
    freeNode(node->right);
    freeNode(node->center); // Free memory of the center node
    free(node->token_instance); // Free memory of token_instance array
    free(node);
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

