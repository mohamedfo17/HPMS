#include "doctors.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    strcpy(newDoc->name, name);
    strcpy(newDoc->speciality, speciality);
    strcpy(newDoc->address, address);
    newDoc->age = age;
   
    newDoc->rank = rank;
    newDoc->department = department;

    
    initId(newDoc->id, name, age, rank, employeNum);
    doctors[employeNum] = newDoc;  // Store pointer in array
    addDocToDepa(newDoc);
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

void maxPatientsCheck(doctor doctor){

        if (doctor.rank=0)
        {
            doctor.maxPatients=4;//visit only cases
        }
        if (doctor.rank=1)
        {
            doctor.maxPatients=8;//visit only and normal cases
        }
        if (doctor.rank=2)
        {
         doctor.maxPatients=14;//visit  and normal  and danger cases

        }
        if (doctor.rank=3)
        {
         doctor.maxPatients=10;//high  and danger cases

        }
        if (doctor.rank=4)
        {
         doctor.maxPatients=5;// danger cases

        }
        
        

}