#include "../headers/patients.h"
#include "../headers/doctors.h"
#include "../headers/departments.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Statically initialize departments
departmentInfo departments[4] = {
    {lab, {NULL}, {NULL}, 0, 0,{7,0,7},{40,0,40},10000,0},
    {cardiology, {NULL}, {NULL}, 0, 0,{7,0,7},{40,0,40},10000,0},
    {physiology, {NULL}, {NULL}, 0, 0,{7,0,7},{40,0,40},10000,0},
    {neurology, {NULL}, {NULL}, 0, 0,{7,0,7},{40,0,40},10000,0}
};

void addDocToDepa(doctor* doc) {
    // Add doctor to department at the next available position
    int depIndex = doc->department - 1;
    departments[depIndex].doctors[departments[depIndex].numDoc] = doc;
    departments[depIndex].numDoc++;
    

    
}

int addPatientToDepa(patient* patient) {

    int depIndex = patient->department - 1;
    if (patient->condition <= 0 || patient->condition > 4) {
        printf("Error: Invalid patient condition %d\n", patient->condition);
        return 0;
    }
    
    if (patient->condition >= 1 && patient->condition <= 2) {
        if (departments[depIndex].surgeryRoomsDepa.busy + 1 <= departments[depIndex].surgeryRoomsDepa.total) {
            printf("Adding patient to surgery room n%d in department of %s\n", 
                   departments[depIndex].surgeryRoomsDepa.busy + 1, 
                   departmentToString(departments[depIndex].department));
            departments[depIndex].surgeryRoomsDepa.busy++;
            departments[depIndex].surgeryRoomsDepa.empty--;
            
            departments[depIndex].patients[departments[depIndex].numPat] = patient;
            departments[depIndex].numPat++;
            
            return 1;
        } else {
            printf("There is no free surgery room in the department of %s\nDeporting to new hospital\n", 
                   departmentToString(departments[depIndex].department));
            return 0;
        }
    } else if (patient->condition >= 3 && patient->condition <= 4) {
        if (departments[depIndex].patientRoomsDepa.busy + 1 <= departments[depIndex].patientRoomsDepa.total) {
             printf("Adding patient to patient room n%d in department of %s\n", 
                   departments[depIndex].patientRoomsDepa.busy + 1, 
                   departmentToString(departments[depIndex].department));
            departments[depIndex].patientRoomsDepa.busy++;
            departments[depIndex].patientRoomsDepa.empty--;
            
            departments[depIndex].patients[departments[depIndex].numPat] = patient;
            departments[depIndex].numPat++;
            
            return 1;
        } else {
            printf("There is no free patient room in the department of %s\nDeporting to new hospital\n", 
                   departmentToString(departments[depIndex].department));
            return 0;
        }
    }
    
    return 0;
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