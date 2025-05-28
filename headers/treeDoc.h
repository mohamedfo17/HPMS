#ifndef TREEDOC_H
#define TREEDOC_H
#include "doctors.h"

struct doctor;



typedef struct Node {
    char data[14];
    struct doctor *doctor;
    struct Node* left;
    struct Node* right;
} TreeNode;

TreeNode* createNode(char data[14], struct doctor *doctor);
TreeNode* insertTree(TreeNode *root, doctor *doctor, char data[14], rank rank, int *firstInser, int *flip);
doctor* search(TreeNode *root, char id[14], rank rank, int *firstSearch) ;
TreeNode* deleteNode(TreeNode* root,  char data[14], rank rank, int *firstSearch);
void inorderTraversal(TreeNode *root);

#endif