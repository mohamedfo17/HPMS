#include "../headers/departments.h"
#include "../headers/stack.h"
#include "../headers/patients.h"
#include "../headers/treePat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




stack* createStack(stack **top){
    *top=NULL;
    return *top;
}


void push(stack **top, patient *patient) {
    stack *newNode = (stack*)malloc(sizeof(stack));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->patient = patient;
    newNode->next = *top;
    *top = newNode;

   // deleteFromQueue(patient->id);
    deletePat(patient->id, patient->condition, patient->department);

    printf("Patient %s is discharged\n", patient->name);
}


void pop(stack **top){
    if ((*top==NULL))
    {
        printf("No patient have been discharged\n");
        return;
    }
    stack *temp=*top;
    patient *backPat=temp->patient;
    *top=(*top)->next;
    addPatient(backPat->name,backPat->age,backPat->medicalCase,backPat->address,backPat->condition,backPat->department);

    free(temp);


    
}