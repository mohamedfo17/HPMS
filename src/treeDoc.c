#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/treeDoc.h"
#include "../headers/patients.h"
#include "../headers/doctors.h"



// Create a new TreeNode for a doctor
TreeNode* createNode(char data[14], doctor *doctor) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    strcpy(newNode->data, data);
    newNode->doctor = doctor;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert a doctor into the tree
TreeNode* insertTree(TreeNode *root, doctor *doctor, char data[14], rank rank, int *firstInser, int *flip) {
    if (root == NULL) {
        return createNode(data, doctor);
    }

    if (*firstInser == 0) {
        *firstInser = 1;

        if (rank == 0 || rank == 1) {
            root->right = insertTree(root->left, doctor, data, rank, firstInser, flip);
        } else {
            root->left = insertTree(root->right, doctor, data, rank, firstInser, flip);
        }
    } else if (*firstInser == 1) {
        if (*flip == 0) {
            root->left = insertTree(root->left, doctor, data, rank, firstInser, flip);
            *flip = 1;
        } else {
            root->right = insertTree(root->right, doctor, data, rank, firstInser, flip);
            *flip = 0;
        }
    }

    return root;
}

// Find the node with minimum data (used in deletion)
TreeNode* findMin(TreeNode* root) {
    TreeNode* current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Delete a doctor from the tree
TreeNode* deleteNode(TreeNode* root,  char data[14], rank rank, int *firstSearch) {
    if (root == NULL) {
        return NULL;
    }

    if (strcmp(root->data, data) == 0) {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        } else {
            TreeNode* temp = findMin(root->right);
            strcpy(root->data, temp->data);
            root->doctor = temp->doctor;
            root->right = deleteNode(root->right,  temp->data, rank, firstSearch);
        }
    } else {
        if (*firstSearch == 0) {
            *firstSearch = 1;
            if (rank == 0 || rank == 1) {
                root->left = deleteNode(root->left,  data, rank, firstSearch);
            } else {
                root->right = deleteNode(root->right,  data, rank, firstSearch);
            }
        } else {
            root->left = deleteNode(root->left,  data, rank, firstSearch);
            root->right = deleteNode(root->right,  data, rank, firstSearch);
        }
    }

    return root;
}

// Search for a doctor node by ID
doctor* search(TreeNode *root, char id[14], rank rank, int *firstSearch) {
    if (root == NULL) {
        return NULL;
    }

    if (strcmp(root->data, id) == 0) {
        return root->doctor;
    }

    doctor *result = NULL;

    if (*firstSearch == 0) {
        *firstSearch = 1;

        if (rank == 0 || rank == 1) {
            result = search(root->left, id, rank, firstSearch);
        } else {
            result = search(root->right, id, rank, firstSearch);
        }

        if (result != NULL) return result;
    }

    result = search(root->left, id, rank, firstSearch);
    if (result != NULL) return result;

    return search(root->right, id, rank, firstSearch);
}
