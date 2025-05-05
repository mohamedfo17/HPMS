#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/treePat.h"
#include "../headers/patients.h"
#include "../headers/doctors.h"

int n = 0;
int *firstInsert = &n;
int f = 0;
int *flip = &f;
int g = 0;
int *firstSearch = &g;

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
        (*firstInser) = 1;

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

TreeNode* deleteNode(TreeNode* root, patient *patient, char data[14], condition condition) {
    if (root == NULL) {
        return root;
    }

    if (condition == 0 || condition == 1) {
        root->left = deleteNode(root->left, patient, data, condition);
    } else if (condition >= 2) {
        root->right = deleteNode(root->right, patient, data, condition);
    } else {
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
            root->right = deleteNode(root->right, patient, temp->data, condition);
        }
    }

    return root;
}

TreeNode* search(TreeNode *root, char id[14], condition condition) {
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
            result = search(root->left, id, condition);
        } else if (condition >= 2) {
            result = search(root->right, id, condition);
        }

        if (result != NULL) return result;
    }

    result = search(root->left, id, condition);
    if (result != NULL) return result;

    return search(root->right, id, condition);
}
