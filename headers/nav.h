#ifndef NAV_H     
#define NAV_H

#include "stack.h"  // Include stack.h to make sure stack type is defined
extern stack *top;
void homePage();
void managePatients();
void manageDoctors();
void dischargePatient(struct stack **top);  // Fixed to use struct consistently
void viewWaitingQueue();
void addPatientToQueue();
void undoLastDischarge(struct stack **top);
void searchPatientInTree();
void viewHospitalStructure();
void saveDataToFile();
void loadDataFromFile();
void manageSessionsNav(struct stack **top);

// Patient management functions
void addPatientNav();
void editPatientNav();
void viewPatientNav();
void deletePatientNav();

// Doctor management functions
void addDoctorNav();
void editDoctorNav();
void viewDoctorNav();
void deleteDoctorNav();
void patientRepoNav();

#endif