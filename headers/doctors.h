// In doctors.h
#ifndef DOCTOR_H
#define DOCTOR_H
#include <stdio.h>
#include <stdlib.h>
#include "patients.h"
#include "departments.h"

typedef enum rankDoc {
    intern=1, low, med, high, chief, president  
} rank;

typedef struct doctor {
    char name[30];
    int age;
    char speciality[40];
    char address[150];
    rank rank;
    int numPatients;
    int maxPatients;
    department department;
    char id[14];
} doctor;

extern int employeNum;  // Declare the global variable

void addDoctor(char name[30], int age, char speciality[30], char address[150], rank rank, department department);
void initId(char id[14], const char name[30], int age, rank rank, int employeNum);
doctor* assignDoc(patient *patient);
int maxPatientsCheck(doctor doctor);
doctor* findDocById(char id[14], rank searchRank);
const char *rankToString(rank rank) ;
void deleteDoc(char id[14], department searchDepartment, rank searchRank);
void viewAllDoctors();
void updateDoctorName(doctor *doctor, char name[30]);
void updateDoctorAge(doctor *doctor, int age);
void updateDoctorSpecialty(doctor *doctor, char specialty[200]);
void updateDoctorAddress(doctor *doctor, char address[150]);
void updateDoctorRank(doctor *doctor, rank rank, department department);
void updateDoctorDepartment(doctor *doctor, department department);
void updateDoctor(doctor *doctor, char name[30], int age, char specialty[200], char address[150], rank rank, department department);
int checkPositionAvailibility(rank rank,department department);
#endif