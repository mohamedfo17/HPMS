#include "../headers/patients.h"
#include "doctors.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "treePat.c"
 int patientNum = 0; 
 int n = 0;
int *firstInsert = &n;
int f = 0;
int *flip = &f;
int g = 0;
int *firstSearch = &g;
patient* patients[200];  // Array of pointers to patient structs
TreeNode *rootEmePat=NULL;
TreeNode *rootCarPat=NULL;
TreeNode *rootPhyPat=NULL;
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
    newPatient->assignedDoc = assignDoc(newPatient);
    
    initId(newPatient->id, name, age, condition, patientNum);
    patients[patientNum] = newPatient;
    addPatientToDepa(newPatient);
    if (newPatient->department == 0) {
        rootEmePat = insertTree(rootEmePat,newPatient, newPatient->id, condition,firstInsert,flip);
        *firstInsert=1;
    } else if (newPatient->department == 1) {
        rootCarPat = insertTree(rootCarPat,newPatient, newPatient->id, condition,firstInsert,flip);
        *firstInsert=1;
    } else if (newPatient->department == 2) {
        rootPhyPat = insertTree(rootPhyPat,newPatient, newPatient->id, condition,firstInsert,flip);
        *firstInsert=1;
    } ;
    patientNum++;
        printf("Patient added successfully!\n");

}

void viewAllPatients(){
    for (int i = 0; i < patientNum; i++)
    {
        printf("-The patient number %d is %s\n",i+1,patients[i]->name);
    }
    managePatients();
    
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
TreeNode* findPatientById(char id[14],condition searchCondition) {
    TreeNode* foundNode = NULL;
    if (rootEmePat != NULL) {
        foundNode = search(rootEmePat, id, searchCondition, firstSearch);
    }
    if (foundNode == NULL && rootCarPat != NULL) {
        foundNode = search(rootCarPat, id, searchCondition, firstSearch);
    }
    if (foundNode == NULL && rootPhyPat != NULL) {
        foundNode = search(rootPhyPat, id, searchCondition, firstSearch);
    }
    return foundNode;

}
void deletePat(char id[14],condition searchCondition,department searchDepartment) {
    TreeNode* foundNode = NULL;
    if (searchDepartment == 0) {
        rootEmePat = deleteNode(rootEmePat, foundNode->patient, id, searchCondition, firstSearch);
    } else if (searchDepartment == 1) {
        rootCarPat = deleteNode(rootCarPat, foundNode->patient, id, searchCondition, firstSearch);
    } else if (searchDepartment == 2) {
        rootPhyPat = deleteNode(rootPhyPat, foundNode->patient, id, searchCondition, firstSearch);
    }
}