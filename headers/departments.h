#ifndef DEPARTMENTS_H     
#define DEPARTMENTS_H

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
    doctor* doctors[20]; 
    patient* patients[50];  
    int numDoc;
    int numPat; 
    surgeryRooms surgeryRoomsDepa;
    patientRooms patientRoomsDepa;
    float balence;
    float income;
    float expenses;
} departmentInfo;
extern departmentInfo departments[4];
void addDocToDepa(doctor* doc);
int addPatientToDepa(struct patient* patient);
const char* departmentToString(department department);
void deleteDocFromDepa(doctor* doc);
void deletePatientFromDepa(patient* pat);
#endif
