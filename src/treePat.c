#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/treePat.h"
#include "../headers/patients.h"
#include "../headers/doctors.h"

TreeNodePat* createNodePat(char data[14], patient *patient) {
    TreeNodePat *newNode = (TreeNodePat *)malloc(sizeof(TreeNodePat));
    strcpy(newNode->data, data);
    newNode->patient = patient;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNodePat* insertTreePat(TreeNodePat *root, patient *patient, char data[14], condition condition, int *firstInser, int *flip) {
    if (root == NULL) {
        return createNodePat(data, patient);
    }
    
    if (*firstInser == 0) {          
        if (condition == 2 || condition == 1) {
            root->right = insertTreePat(root->left, patient, data, condition, firstInser, flip);
        } else if (condition >= 3) {
            root->left = insertTreePat(root->right, patient, data, condition, firstInser, flip);
        }
    } else if (*firstInser == 1) {
        if (*flip == 0) {
            root->left = insertTreePat(root->left, patient, data, condition, firstInser, flip);
            *flip = 1;
        } else {
            root->right = insertTreePat(root->right, patient, data, condition, firstInser, flip);
            *flip = 0;
        }
    }
    
    return root;
}

TreeNodePat* findMinPat(TreeNodePat* root) {
    TreeNodePat* current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

TreeNodePat* deleteNodePat(TreeNodePat* root, char data[14], condition condition, int *firstSearch) 
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
            TreeNodePat* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNodePat* temp = root->left;
            free(root);
            return temp;
        } else {
            TreeNodePat* temp = findMinPat(root->right);
            strcpy(root->data, temp->data);
            root->patient = temp->patient;
            root->right = deleteNodePat(root->right, temp->data, condition, firstSearch);
        }
    } else {
        if (*firstSearch == 0) {
            *firstSearch = 1;
            if (condition == 2 || condition == 1) {
                root->left = deleteNodePat(root->left, data, condition, firstSearch);
            } else {
                root->right = deleteNodePat(root->right, data, condition, firstSearch);
            }
        } else {
            root->left = deleteNodePat(root->left, data, condition, firstSearch);
            root->right = deleteNodePat(root->right, data, condition, firstSearch);
        }
    }
    
    return root;
}

patient* searchPat(TreeNodePat *root, char id[14], condition condition, int *firstSearch) {
    if (root == NULL) {
        return NULL;
    }
    
    if (strcmp(root->data, id) == 0) {
        return root->patient;
    }
    
    patient *result = NULL;
    
    if (*firstSearch == 0) {
        *firstSearch = 1;
        
        if (condition == 2 || condition == 1) {
            result = searchPat(root->left, id, condition, firstSearch);
        } else if (condition >= 2) {
            result = searchPat(root->right, id, condition, firstSearch);
        }
        
        if (result != NULL) return result;
    }
    
    result = searchPat(root->left, id, condition, firstSearch);
    if (result != NULL) return result;
    
    return searchPat(root->right, id, condition, firstSearch);
}