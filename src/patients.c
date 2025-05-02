#include "patients.h"
#include "doctors.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int patientNum = 0; 
patient* patients[2000];  // Array of pointers to patient structs

void addPatient(char name[30], int age, char medicalCase[200], char address[150], condition condition, department department, doctor assignedDoc) {
    patient *newPatient = (patient*)malloc(sizeof(patient));
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
}