#ifndef DEPARTMENTS_H     
#define DEPARTMENTS_H
#include "patients.h"

// Forward declarations
typedef struct doctor doctor;
typedef struct patient patient;

typedef enum {
    lab, cardiology, physiology, emergency
} department;

typedef struct {
    department department;
    doctor* doctors[20];  // Use pointer instead of array
    patient* patients[50];  // Fixed array size for patients
    int numDoc;
    int numPat;  // Added counter for patients
} departmentInfo;

void addDocToDepa(doctor* doc);
void addPatientToDepa(patient* patient);

#endif
