#include "../headers/patients.h"
#include "doctors.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int patientNum = 0; 
patient* patients[200];  // Array of pointers to patient structs

void addPatient(char name[30], int age, char medicalCase[200], char address[150], condition condition, department department) {
    patient *newPatient = (patient*)malloc(sizeof(patient));
    if (newPatient==NULL)
    {
       printf("failed to add patient");
       return;
    }
    
    strcpy(newPatient->name, name);
    strcpy(newPatient->medicalCase, medicalCase);
    strcpy(newPatient->address, address);
    newPatient->age = age;
    newPatient->condition = condition;
    newPatient->department = department;
    newPatient->assignedDoc = assignDoc(newPatient);
    
    initId(newPatient->id, name, age, condition, patientNum);
    patients[patientNum] = newPatient;
    addPatientToDepa(newPatient);
    patientNum++;
        printf("Patient added successfully!\n");

}

void viewAllPatients(){
    for (int i = 0; i < patientNum; i++)
    {
        printf("-The patient number %d is %s\n",i+1,patients[i]->name);
    }
    managePatients();
    
}
void updatePatientName(char patientID[14],char name[30]){
    
};
char* conditionToString(condition cond) {
    static char condStr[10]; // Static so it persists after function returns
    
    switch (cond) {
        case urgence:
            strcpy(condStr, "urgence");
            break;
        case danger:
            strcpy(condStr, "danger");
            break;
        case normal:
            strcpy(condStr, "normal");
            break;
        case visit:
            strcpy(condStr, "visit");
            break;
        default:
            strcpy(condStr, "unknown");
    }
    
    return condStr;
}