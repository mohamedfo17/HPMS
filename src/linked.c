#include "../headers/patients.h"
#include "../headers/doctors.h"
#include "../headers/linked.h"
#include <stdio.h>
#include <stdlib.h>

void deleteList(list **patHead, patient *pat) {
    if (patHead == NULL || *patHead == NULL || pat == NULL) {
        printf("Invalid parameters for deletion\n");
        return;
    }

    list *current = *patHead;
    list *prev = NULL;

    while (current != NULL && current->pat != pat) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Patient not found in list\n");
        return;
    }

    if (prev == NULL) {
        *patHead = current->next; 
    } else {
        prev->next = current->next;
    }

    free(current);
}

void insertList(list **patHead, patient *pat) {
    if (pat == NULL) {
        printf("Error: Cannot insert null patient\n");
        return;
    }

    list *newNode = (list*)malloc(sizeof(list));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    newNode->pat = pat;
    newNode->next = NULL;

    if (*patHead == NULL) {
        *patHead = newNode;
    } else {
        list *current = *patHead;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}