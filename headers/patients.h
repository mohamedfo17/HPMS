#ifndef PATIENT_H     
#define PATIENT_H
#include <stdio.h>
#include <stdlib.h>
#include "doctors.h"
#include "departments.h"


typedef enum condition {
    danger,normal,visit
} condition;

typedef struct 
{
    char name[30];
    int age;
    char medicalCase[200];
    char address[150];
    condition condition;
    doctor *assignedDoc;
    department department;
    char id[14];
}patient;

void addPatient(char name[30], int age, char medicalCase[200], char address[150], condition condition,department department,doctor assignedDoc);









#endif
