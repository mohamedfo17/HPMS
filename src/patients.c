#include "../headers/patients.h"
#include "../headers/treePat.h"
#include "../headers/departments.h"


#include "../headers/doctors.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 int patientNum = 0; 
 int np = 0;
int *firstInsertP = &np;
int fP = 0;
int *flipP = &fP;
int gP = 0;
int *firstSearchP = &gP;
patient* patients[200];  // Array of pointers to patient structs
TreeNodePat *rootEmePat=NULL;
TreeNodePat *rootCarPat=NULL;
TreeNodePat *rootPhyPat=NULL;
void addPatient(char name[30], int age, char medicalCase[200], char address[150], condition condition, department department) {
    patient *newPatient = (patient*)malloc(sizeof(patient));
    if (newPatient==NULL)
    {
       printf("failed to add patient");
       return;
    }
    
    strcpy(newPatient->name, name);
    strcpy(newPatient->medicalCase, medicalCase);
    strcpy(newPatient->address, address);
    newPatient->age = age;
    newPatient->condition = condition;
    newPatient->department = department;
   // newPatient->assignedDoc = assignDoc(newPatient);
    
    initId(newPatient->id, name, age, condition, patientNum);
    patients[patientNum] = newPatient;
    addPatientToDepa(newPatient);
    if (newPatient->department == 0) {
        rootEmePat = insertTreePat(rootEmePat,newPatient, newPatient->id, condition,firstInsertP,flipP);
        *firstInsertP=1;
    } else if (newPatient->department == 1) {
        rootCarPat = insertTreePat(rootCarPat,newPatient, newPatient->id, condition,firstInsertP,flipP);
        *firstInsertP=1;
    } else if (newPatient->department == 2) {
        rootPhyPat = insertTreePat(rootPhyPat,newPatient, newPatient->id, condition,firstInsertP,flipP);
        *firstInsertP=1;
    } ;
    patientNum++;
        printf("Patient added successfully!\n");
        printf("Patient Id is %s\n",newPatient->id);


}

void viewAllPatients(){
    printf("1-view only names\n-2view names and ids");
    int choice;
    scanf("%d", &choice);
    if (choice==1)
    {
   
    for (int i = 0; i < patientNum; i++)
    {
        printf("-The patient number %d is %s\n",i+1,patients[i]->name);
    }} else if(choice==2){
        for (int i = 0; i < patientNum; i++)
    {
            printf("-The patient number %d is %s\n his id is %s\n",i+1,patients[i]->name,patients[i]->id);
        }}
    //manage patients
    
}
void updatePatientName(char patientID[14],char name[30]){
    
};
char* conditionToString(condition cond) {
    static char condStr[10]; // Static so it persists after function returns
    
    switch (cond) {
        case urgence:
            strcpy(condStr, "urgence");
            break;
        case danger:
            strcpy(condStr, "danger");
            break;
        case normal:
            strcpy(condStr, "normal");
            break;
        case visit:
            strcpy(condStr, "visit");
            break;
        default:
            strcpy(condStr, "unknown");
    }
    
    return condStr;
}
patient* findPatientById(char id[14],condition searchCondition) {
    patient* foundNode = NULL;
    if (rootEmePat != NULL) {
        foundNode = searchPat(rootEmePat, id, searchCondition, firstSearchP);
    }
    if (foundNode == NULL && rootCarPat != NULL) {
        foundNode = searchPat(rootCarPat, id, searchCondition, firstSearchP);
    }
    if (foundNode == NULL && rootPhyPat != NULL) {
        foundNode = searchPat(rootPhyPat, id, searchCondition, firstSearchP);
    }
    return foundNode;

}
void deletePat(char id[14],condition searchCondition,department searchDepartment) {
    TreeNodePat* foundNode = NULL;
    if (searchDepartment == 0) {
        rootEmePat = deleteNodePat(rootEmePat, id, searchCondition, firstSearchP);
    } else if (searchDepartment == 1) {
        rootCarPat = deleteNodePat(rootCarPat, id, searchCondition, firstSearchP);
    } else if (searchDepartment == 2) {
        rootPhyPat = deleteNodePat(rootPhyPat, id, searchCondition, firstSearchP);
    }
}