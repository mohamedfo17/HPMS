#ifndef PATIENT_H     
#define PATIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "doctors.h"
#include "departments.h"



typedef enum condition {
    urgence=1,danger,normal,visit
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
    bool isAssured;
    float sessionCost;
} patient;

void addPatient(char name[30], int age, char medicalCase[200], char address[150], condition condition, department department,bool isAssured);



void viewAllPatients();

void updatePatientName(patient *patient,char name[30]);
void updatePatientAge(patient *patient,int age);
void updatePatientMedicalCase(patient *patient,char medicalCase[200]);
void updatePatientAddress(patient *patient,char address[150]);
void updatePatientCondition(patient *patient,condition condition,department department);
void updatePatientDepartment(patient *patient,department department);
void updatePatient(patient *patient,char name[30],int age,char medicalCase[200],char address[150],condition condition,department department);
char* conditionToString(condition cond);
patient* findPatientById(char id[14],condition searchCondition);

void deletePat(char id[14],condition searchCondition,department searchDepartment);

int sessionCost(patient *patient);

void generateRepo();
void generateOneRepo();




#endif
