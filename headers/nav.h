#ifndef NAV_H     
#define NAV_H
#include "stack.h" // or wherever stack is defined

void dischargePatient(stack **top);

void homePage();
void managePatients();
void manageDoctors();
void dischargePatient( struct stack **top);
void viewWaitingQueue();
void addPatientToQueue();
void undoLastDischarge();
void searchPatientInTree();
void viewHospitalStructure();
void saveDataToFile();
void loadDataFromFile();

// Patient management functions
void addPatientNav();
void editPatientNav();
void viewPatientNav();
void deletePatientNav();


//
void addDoctorNav();
void editDoctorNav();
void viewDoctorNav();
void deleteDoctorNav();

#endif
