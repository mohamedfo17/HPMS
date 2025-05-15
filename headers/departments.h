#ifndef DEPARTMENTS_H     
#define DEPARTMENTS_H

// Forward declarations
typedef struct doctor doctor;
typedef struct patient patient;

typedef enum {
    lab=1, cardiology, physiology, neurology
} department;
typedef struct patientRooms{
   int total,busy,empty;
}patientRooms;
typedef struct surgeryRooms{
   int total,busy,empty;
}surgeryRooms;
typedef struct {
    department department;
    doctor* doctors[20];  // Use pointer instead of array
    patient* patients[50];  // Fixed array size for patients
    int numDoc;
    int numPat;  // Added counter for patients
    surgeryRooms surgeryRoomsDepa;
    patientRooms patientRoomsDepa;
    float balence;
    float income;
} departmentInfo;
extern departmentInfo departments[4];
void addDocToDepa(doctor* doc);
int addPatientToDepa(struct patient* patient);
const char* departmentToString(department department);
void deleteDocFromDepa(doctor* doc);
void deletePatientFromDepa(patient* pat);
#endif
