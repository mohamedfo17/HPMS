#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/treeDoc.h"
#include "../headers/patients.h"
#include "../headers/doctors.h"
int n=0;
int *firstInsert=&n;
int f=0;
int *flip=&f;
int g=0;//maybe you will need to declare them in doc and pat header files
int *firstSearch=&g;
TreeNode* createNode(char data[14],doctor *doctor){
    TreeNode *newNode=(TreeNode *)malloc(sizeof(TreeNode));
    strcpy(newNode->data, data);
    newNode->doctor=doctor;

    newNode->right=NULL;
    newNode->left=NULL;
    return newNode;
};

TreeNode* insertTree(TreeNode *root, doctor *doctor, char data[14], condition condition,int *firstInser,int *flip){
    if (root == NULL) {
       return createNode(data,doctor);
    }
    if (*firstInser==0)
    {
       (*firstInser)=1;
    
    
    if (condition==0||condition==1)
    {
        root->right=insert(root->left, doctor, data, condition);
    }else if (condition>=2)
    {
        root->left=insert(root->right, doctor, data, condition);
    }}
    else if (firstInser==1)
    {
        if (flip==0)
        {
            root->left=insert(root->left, doctor, data, condition);
            *flip=1;
        }else if (flip==1)
        {
            root->right=insert(root->right, doctor, data, condition);
            *flip=0;
        }
    }
    
    return root;
};

TreeNode* findMin(TreeNode* root) {
    TreeNode* current = root;
    
    while (current && current->left != NULL) {
        current = current->left;
    }
    
    return current;
}

TreeNode* deleteNode(TreeNode* root, doctor *doctor, char data[14], condition condition) {
    
    if (root == NULL) {
        return root;
    }
    
    // Recursively find the node to be deleted
    if (condition==0||condition==1) {
        root->left = deleteNode(root->left, doctor, data, condition);
    }
    else if (condition>=2) {
        root->right = deleteNode(root->right, doctor, data, condition);
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
            
            strcpy(root->data, temp->data);
            root->right = deleteNode(root->right, doctor, temp->data, condition);
        }
    }
    
    return root;
}
TreeNode* search(TreeNode *root, char id[14], rank rank) {
    if (root == NULL) {
        return NULL;
    }

    if (strcmp(root->data, id) == 0) {
        return root->doctor; //found him
    }

    TreeNode *result = NULL;

    if (*firstSearch == 0) {
        *firstSearch = 1;

        // First search direction based on rank
        if (rank == 0 || rank == 1) {
            result = search(root->left, id, rank);
        } else if (rank >= 2) {
            result = search(root->right, id, rank);
        }

        if (result != NULL) return result; // Found it in preferred direction
    }

    // Continue search in both directions if not found
    result = search(root->left, id, rank);
    if (result != NULL) return result;

    return search(root->right, id, rank);
}

