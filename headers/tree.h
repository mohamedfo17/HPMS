#ifndef TREE_H     
#define TREE_H
#include "doctors.h"

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};
typedef struct Node TreeNode;

TreeNode createNode(int data);
TreeNode insert(TreeNode *root, int data,rank rank);
TreeNode search(TreeNode *root, int data);
void inorderTraversal(TreeNode *root);
TreeNode deleteNode(TreeNode *root, int data);




#endif
