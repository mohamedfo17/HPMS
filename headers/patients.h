#ifndef PATIENT_H     
#define PATIENT_H
#include <stdio.h>
#include <stdlib.h>
#include "doctors.h"
#include "departments.h"


typedef enum condition {
    urgence,danger,normal,visit
} condition;

typedef struct patient 
{
    char name[30];
    int age;
    char medicalCase[200];
    char address[150];
    condition condition;
    doctor *assignedDoc;
    department department;
    char id[14];
} patient;

void addPatient(char name[30], int age, char medicalCase[200], char address[150], condition condition,department department,doctor assignedDoc);



void viewAllPatients();

void updatePatientName(char patientID[14],char name[30]);
void updatePatientAge(char patientID[14],int age);
void updatePatientMedicalCase(char patientID[14],char medicalCase[200]);
void updatePatientAddress(char patientID[14],char address[150]);
void updatePatientCondition(char patientID[14],condition condition);
void updatePatientDepartment(char patientID[14],department department);
void updatePatient(char patientID[30],char name[30],int age,char medicalCase[200],char address[150],condition condition,department department);
char conditionToString(condition condition);

TreeNode* findPatientById(char id[14],condition searchCondition);







#endif
