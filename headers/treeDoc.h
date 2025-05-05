#ifndef TREEDOC_H     
#define TREEDOC_H
#include "doctors.h"

struct Node {
    char data[14];
    doctor *doctor;
    struct Node* left;
    struct Node* right;
};
typedef struct Node TreeNode;

TreeNode* createNode(char id[14]);
TreeNode* insertTree(TreeNode *root, doctor *doctor,char id[14],rank rank);
TreeNode* search(TreeNode *root, char id[14]);
void inorderTraversal(TreeNode *root);
TreeNode* deleteNode(TreeNode *root,doctor *doctor, char id[14],rank rank);




#endif
