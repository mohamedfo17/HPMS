#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/treePat.h"
#include "../headers/patients.h"
#include "../headers/doctors.h"



TreeNode* createNode(char data[14], patient *patient) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    strcpy(newNode->data, data);
    newNode->patient = patient;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* insertTree(TreeNode *root, patient *patient, char data[14], condition condition, int *firstInser, int *flip) {
    if (root == NULL) {
        return createNode(data, patient);
    }

    if (*firstInser == 0) {
        

        if (condition == 0 || condition == 1) {
            root->right = insertTree(root->left, patient, data, condition, firstInser, flip);
        } else if (condition >= 2) {
            root->left = insertTree(root->right, patient, data, condition, firstInser, flip);
        }
    } else if (*firstInser == 1) {
        if (*flip == 0) {
            root->left = insertTree(root->left, patient, data, condition, firstInser, flip);
            *flip = 1;
        } else {
            root->right = insertTree(root->right, patient, data, condition, firstInser, flip);
            *flip = 0;
        }
    }

    return root;
}

TreeNode* findMin(TreeNode* root) {
    TreeNode* current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

TreeNode* deleteNode(TreeNode* root, char data[14], condition condition, int *firstSearch)
 {
    if (root == NULL) {
        return NULL;
    }

    if (strcmp(root->data, data) == 0) {
        // Node to delete found
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
            root->patient = temp->patient;
            root->right = deleteNode(root->right,  temp->data, condition, firstSearch);
        }
    } else {
        if (*firstSearch == 0) {
            *firstSearch = 1;
            if (condition == 0 || condition == 1) {
                root->left = deleteNode(root->left,  data, condition, firstSearch);
            } else {
                root->right = deleteNode(root->right,  data, condition, firstSearch);
            }
        } else {
            root->left = deleteNode(root->left,  data, condition, firstSearch);
            root->right = deleteNode(root->right,  data, condition, firstSearch);
        }
    }

    return root;
}

TreeNode* search(TreeNode *root, char id[14], condition condition, int *firstSearch) {
    if (root == NULL) {
        return NULL;
    }

    if (strcmp(root->data, id) == 0) {
        return root->patient;
    }

    TreeNode *result = NULL;

    if (*firstSearch == 0) {
        *firstSearch = 1;

        if (condition == 0 || condition == 1) {
            result = search(root->left, id, condition, firstSearch);
        } else if (condition >= 2) {
            result = search(root->right, id, condition, firstSearch);
        }

        if (result != NULL) return result;
    }

    result = search(root->left, id, condition,firstSearch);
    if (result != NULL) return result;

    return search(root->right, id, condition,firstSearch);
}
