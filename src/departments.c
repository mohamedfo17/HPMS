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
void deleteDocFromDepa(doctor* doc) {
    if (doc == NULL) {
        return;
    }
    
    int depIndex = doc->department - 1;  // Assuming department numbers start at 1.
    
    // Safety check: if department index is out of bounds,
    // (this assumes NUM_DEPARTMENTS is defined appropriately)
    if (depIndex < 0 || depIndex >= 4) {
        return;
    }
    
    int found = -1;
    // Search for the doctor in the department's list
    for (int i = 0; i < departments[depIndex].numDoc; i++) {
        if (departments[depIndex].doctors[i] == doc) {
            found = i;
            break;
        }
    }
    
    // If found, shift the array left by one position to remove the doctor
    if (found != -1) {
        for (int i = found; i < departments[depIndex].numDoc - 1; i++) {
            departments[depIndex].doctors[i] = departments[depIndex].doctors[i + 1];
        }
        departments[depIndex].numDoc--;
    }
}
void deletePatientFromDepa(patient* pat) {
    if (pat == NULL) {
        return;
    }
    
    int depIndex = pat->department - 1;  // Assuming department numbers start at 1.
    
    // Safety check: if department index is out of bounds
    if (depIndex < 0 || depIndex >= 4) {
        return;
    }
    
    int found = -1;
    // Search for the patient in the department's list
    for (int i = 0; i < departments[depIndex].numPat; i++) {
        if (departments[depIndex].patients[i] == pat) {
            found = i;
            break;
        }
    }
    
    // If found, shift the array left to remove the patient
    if (found != -1) {
        for (int i = found; i < departments[depIndex].numPat - 1; i++) {
            departments[depIndex].patients[i] = departments[depIndex].patients[i + 1];
        }
        departments[depIndex].numPat--;
    }
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