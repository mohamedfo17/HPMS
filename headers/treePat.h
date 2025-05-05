#ifndef TREEPAT_H
#define TREEPAT_H
#include "patients.h"

struct Node {
    char data[14];
    patient *patient;
    struct Node* left;
    struct Node* right;
};
typedef struct Node TreeNode;

TreeNode createNode(char data[14]);
TreeNode insertTree(TreeNode *root, char data[14], condition condition);
TreeNode search(TreeNode *root, char data[14]);
void inorderTraversal(TreeNode *root);
TreeNode deleteNode(TreeNode *root, char data[14]);

#endif