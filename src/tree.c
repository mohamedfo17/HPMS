#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/tree.h"
#include "../headers/patients.h"
#include "../headers/doctors.h"




TreeNode createNode(int data){
    TreeNode *newNode=(TreeNode *)malloc(sizeof(TreeNode));
    newNode->data=data;
    newNode->right=NULL;
    newNode->left=NULL;
    return  *newNode;
};
TreeNode insert(TreeNode *root, int data,rank rank){
    if (root == NULL) {
        TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        return *newNode;
    }
    if (rank==0||rank==1||rank==2)
    {
        root->right=insert(root->left,data);
    }else if (rank>=3)
    {
        root->left=insert(root->right,data);
    }
    
    return *root;
};
TreeNode* findMin(TreeNode* root) {
    TreeNode* current = root;
    
    while (current && current->left != NULL) {
        current = current->left;
    }
    
    return current;
}

TreeNode* deleteNode(TreeNode* root, int data) {
    
    if (root == NULL) {
        return root;
    }
    
    // Recursively find the node to be deleted
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    }
    
    else {
        // Case 1: Node with no children (leaf node)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // Case 2: Node with only one child
        else if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        // Case 3: Node with two children
        else {
            // Find the inorder successor (smallest node in the right subtree)
            TreeNode* temp = findMin(root->right);
            
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    
    return root;
}

