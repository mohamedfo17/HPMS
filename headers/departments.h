#ifndef DEPARTMENTS_H     
#define DEPARTMENTS_H

// Forward declarations
typedef struct doctor doctor;
typedef struct patient patient;

typedef enum {
    lab=1, cardiology, physiology, neurology
} department;

typedef struct {
    department department;
    doctor* doctors[20];  // Use pointer instead of array
    patient* patients[50];  // Fixed array size for patients
    int numDoc;
    int numPat;  // Added counter for patients
    int surgeryRooms;
    int patientRooms;
    float balence;
} departmentInfo;
extern departmentInfo departments[4];
void addDocToDepa(doctor* doc);
void addPatientToDepa(patient* patient);
const char* departmentToString(department department);
void deleteDocFromDepa(doctor* doc);
void deletePatientFromDepa(patient* pat);
#endif
