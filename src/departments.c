#include "../headers/patients.h"
#include "../headers/doctors.h"
#include "../headers/departments.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Statically initialize departments
departmentInfo departments[4] = {
    {lab, {NULL}, {NULL}, 0, 0},
    {cardiology, {NULL}, {NULL}, 0, 0},
    {physiology, {NULL}, {NULL}, 0, 0},
    {emergency, {NULL}, {NULL}, 0, 0,10}
};

void addDocToDepa(doctor* doc) {
    // Add doctor to department at the next available position
    departments[doc->department].doctors[departments[doc->department].numDoc] = doc;
    departments[doc->department].numDoc++;
}

void addPatientToDepa(patient* patient) {
    // Add patient to department
    departments[patient->department].patients[departments[patient->department].numPat] = patient;
    departments[patient->department].numPat++;
}
const char* departmentToString(department dept) {
    switch (dept) {
        case lab: return "Lab";
        case cardiology: return "Cardiology";
        case physiology: return "Physiology";
        case emergency: return "Emergency";
        default: return "Unknown";
    };
