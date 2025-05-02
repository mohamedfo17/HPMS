#ifndef DOCTOR_H     
#define DOCTOR_H
#include <stdio.h>
#include <stdlib.h>
#include "patients.h"
#include "departments.h"

typedef enum rank {
    intern, low, med, high, cheif, president
} rank;

typedef struct {
    char name[30];
    int age;
    char speciality[40];
    char address[150];
    rank rank;
    int numPatients;
    int maxPatients;
    department department;
    patient assignedPatients[10]; //make it depend on case and on role
    char id[14];
} doctor;

extern int employeNum;  // Declare the global variable

void addDoctor(char name[30], int age, char speciality[30], char address[150], rank rank, int numPatients, int maxPatients,department department);
void initId(char id[14], const char name[30], int age, rank rank, int employeNum);
doctor* assignDoc(patient *patient);
void maxPatientsCheck(doctor doctor);

#endif
