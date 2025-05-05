#include "../headers/doctors.h"
#include "treeDoc.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
TreeNode *rootEmeDoc=NULL;
TreeNode *rootCarDoc=NULL;
TreeNode *rootPhyDoc=NULL;


int employeNum = 0; 
doctor* doctors[200];  // Array of pointers to doctor structs

void initId(char id[14], const char name[30], int age, rank rank, int employeNum) {
    // Copy first 5 chars of name
    for (int i = 0; i < 5; i++) {
        id[i] = name[i];
    }
    
    
    for (int i = 5; i < 8; i++) {
        id[i] = (age % 10) ;
        age = age / 10;
    }
    
    
    id[8] = rank ;
    
    // Convert employeNum to 5 chars 
    for (int i = 9; i < 14; i++) {
        id[i] = (employeNum % 10) + '0';
        employeNum = employeNum / 10;
    }
    
    id[13] = '\0';  // Null terminate the string
}

void addDoctor(char name[30], int age, char speciality[30], char address[150], rank rank,department department) {
    doctor *newDoc = (doctor*)malloc(sizeof(doctor));
    if (newDoc == NULL) {
        printf("failed to add doctor\n");
        return;
    }
    strcpy(newDoc->name, name);
    strcpy(newDoc->speciality, speciality);
    strcpy(newDoc->address, address);
    newDoc->age = age;
   
    newDoc->rank = rank;
    newDoc->department = department;

    switch(rank) {
        case intern: newDoc->maxPatients = 4; break;    // Interns handle visit cases only
        case low: newDoc->maxPatients = 8; break;       // Low handles visit and normal
        case med: newDoc->maxPatients = 14; break;      // Med handles all except urgence
        case high: newDoc->maxPatients = 10; break;     // High handles danger and urgence
        case cheif: newDoc->maxPatients = 5; break;     // Chief handles urgence only
        case president: newDoc->maxPatients = 3; break; // President handles special cases
        default:;//;
    }
    initId(newDoc->id, name, age, rank, employeNum);
    doctors[employeNum] = newDoc;  // Store pointer in array
    addDocToDepa(newDoc);
    if (newDoc->department == 0) {
        rootEmeDoc = insertTree(rootEmeDoc, newDoc->id, rank);
    } else if (newDoc->department == 1) {
        rootCarDoc = insertTree( rootCarDoc, newDoc->id, rank);
    } else if (newDoc->department == 2) {
        rootPhyDoc = insertTree(rootPhyDoc, newDoc->id, rank);
    } ;
    employeNum++;
}

doctor* assignDoc(patient *patient){
    doctor *assignedDoc=NULL;
    switch (patient->condition)
    {
    case 0 :
        //find doctor cheif or high


        break;
    case 1:
        //find doctor normal or low or high worst case intern
        break;
    case 2:
        //find doctor normal or intern
        break;
    default:
        //add to queue 
        break;
    }
    return assignedDoc;

}

int maxPatientsCheck(doctor doctor) {

    if (doctor.rank == 0) {
        return (doctor.maxPatients < 4) ? 1 : 0; // visit only cases
    }
    if (doctor.rank == 1) {
        return (doctor.maxPatients < 8) ? 1 : 0; // visit only and normal cases
    }
    if (doctor.rank == 2) {
        return (doctor.maxPatients < 14) ? 1 : 0; // visit and normal and danger cases
    }
    if (doctor.rank == 3) {
        return (doctor.maxPatients < 10) ? 1 : 0; // high and danger cases
    }
    if (doctor.rank == 4) {
        return (doctor.maxPatients < 5) ? 1 : 0; // danger cases
    }

    return 0; // Default return value
}