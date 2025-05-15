#include "../headers/departments.h"
#include "../headers/stack.h"
#include "../headers/patients.h"
#include "../headers/treePat.h"
#include "../headers/queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

stack* createStack(stack **top){
    *top=NULL;
    return *top;
}

void push(stack **top, patient *pat) {
    stack *newNode = (stack *)malloc(sizeof(stack));
    if (!newNode) {
        printf("Memory allocation failed for stack node\n");
        return;
    }

    newNode->patient = (patient *)malloc(sizeof(patient));
    if (!newNode->patient) {
        printf("Memory allocation failed for patient\n");
        free(newNode);
        return;
    }

    strcpy(newNode->patient->name, pat->name);
    strcpy(newNode->patient->medicalCase, pat->medicalCase);
    strcpy(newNode->patient->address, pat->address);
    strcpy(newNode->patient->id, pat->id);
    newNode->patient->age = pat->age;
    newNode->patient->condition = pat->condition;
    newNode->patient->department = pat->department;
    newNode->patient->assignedDoc = pat->assignedDoc;
    newNode->patient->isAssured = pat->isAssured;
    newNode->next = *top;
    *top = newNode;

    deletefromqueue(pat->assignedDoc->doctorQueue, pat->id);
    deletePat(pat->id, pat->condition, pat->department);

    printf("Patient %s is discharged\n", newNode->patient->name);
}

void pop(stack **top) {
    if (*top == NULL) {
        printf("No patient has been discharged\n");
        return;
    }

    stack *temp = *top;
    patient *backPat = temp->patient;
    *top = (*top)->next;


    addPatient(backPat->name, backPat->age, backPat->medicalCase, backPat->address, backPat->condition, backPat->department,backPat->isAssured);

    free(backPat);
    free(temp);

    printf("Undo discharge completed.\n");
}