#include "../headers/patients.h"
#include "../headers/doctors.h"
#include "../headers/departments.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Statically initialize departments
departmentInfo departments[4] = {
    {lab, {NULL}, {NULL}, 0, 0,5,50,10000},
    {cardiology, {NULL}, {NULL}, 0, 0,5,50,10000},
    {physiology, {NULL}, {NULL}, 0, 0,5,50,10000},
    {neurology, {NULL}, {NULL}, 0, 0,10,50,10000}
};

void addDocToDepa(doctor* doc) {
    // Add doctor to department at the next available position
    int depIndex = doc->department - 1;
    departments[depIndex].doctors[departments[depIndex].numDoc] = doc;
    departments[depIndex].numDoc++;
    
}

void addPatientToDepa(patient* patient) {
    // Add patient to department
    int depIndex = patient->department - 1;
    departments[depIndex].patients[departments[depIndex].numPat] = patient;
    departments[depIndex].numPat++;
}
 const char* departmentToString(department dept) {
    switch (dept) {
        case 1: return "Lab";
        case 2: return "Cardiology";
        case 3: return "Physiology";
        case 4: return "neurology";
        default: return "Unknown";
    };
 }