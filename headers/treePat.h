#ifndef TREEPAT_H
#define TREEPAT_H
#include "patients.h"
struct patient;

typedef struct TreeNodePat {
    char data[14];
    struct patient *patient;
    struct TreeNodePat* left;   // Changed TreeNode to TreeNodePat
    struct TreeNodePat* right;  // Changed TreeNode to TreeNodePat
} TreeNodePat;                  // Changed typedef name to match struct name

// Update all function signatures to use TreeNodePat instead of TreeNode
TreeNodePat* createNodePat(char data[14],struct patient *patient);
TreeNodePat* insertTreePat(TreeNodePat *root,struct patient *patient, char data[14], condition condition, int *firstInser, int *flip);
struct patient* searchPat(TreeNodePat *root, char id[14], condition condition, int *firstSearch);
//void inorderTraversal(TreeNodePat *root);
TreeNodePat* deleteNodePat(TreeNodePat* root, char data[14], condition condition, int *firstSearch);
TreeNodePat* findMinPat(TreeNodePat* root);
#endif