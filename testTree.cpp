//
// Created by Natnail on 3/31/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parser.h"
#include "BuildTree.h"
#include "TreeNode.h"
#include "testTree.h"


void print_inorder_tree(node_t* root, int depth) {
    if (root == NULL) {
        // printf("Error root is Null in PrintAST\n");
        return;
    }
/*
    // Print the current node with appropriate indentation
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
*/
    // Skip printing nodes with label 'X'
    if (root->Label != ' ')
    {
        printf("%*c%c\n", depth*3, ' ', root->Label);
    }//
    else{
        //printf("%c", root->Label);
        // Print token instance if it exists

        if(root->token_id != 0){
            //printf("%d", tokens.tokenid);
            printf("%*c %s, %s\n", depth * 3, ' ', root->token_id, root->token_instance);

        }else{
            //printf("inside of else %d", tokens.tokenid);

            printf("%*c %s\n", depth * 3, ' ', root->token_instance); // this is the only way which i can print the empty with out token being 0

        }

    }

    // Recursively print the left subtree with increased depth
    if(root->left != NULL){
        print_inorder_tree(root->left, depth + 1);
    }

    if(root->center != NULL) {
        print_inorder_tree(root->center, depth + 1);
    }

    // Recursively print the right subtree with increased depth
    if(root->right != NULL) {
        print_inorder_tree(root->right, depth + 1);
    }

    if(root->far_right != NULL) {
        print_inorder_tree(root->far_right, depth + 1);
    }
}


