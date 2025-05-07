#include "../headers/doctors.h"
#include "../headers/treeDoc.h"
#include "../headers/departments.h"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
TreeNode *rootEmeDoc=NULL;
TreeNode *rootCarDoc=NULL;
TreeNode *rootPhyDoc=NULL;
int n=0;
int *firstInsert=&n;
int f=0;
int *flip=&f;
int g=0;//maybe you will need to declare them in doc and pat header files
int *firstSearch=&g;

int employeNum = 0; 
doctor* doctors[200];  // Array of pointers to doctor structs

#include <stdio.h>
#include <string.h>

void initId(char id[15], const char name[30], int age, rank rankValue, int employeeNum) {
    // Copy first 5 letters of name or fill with '_'
    for (int i = 0; i < 5; i++) {
        id[i] = (name[i] != '\0') ? name[i] : '_';
    }

    // Add age as 3 characters
    id[5] = (age / 100) % 10 + '0';
    id[6] = (age / 10) % 10 + '0';
    id[7] = age % 10 + '0';

    // Add rank (convert enum to char)
    id[8] = rankValue + '0';

    // Add employee number as 5 characters
    id[9]  = (employeeNum / 10000) % 10 + '0';
    id[10] = (employeeNum / 1000) % 10 + '0';
    id[11] = (employeeNum / 100) % 10 + '0';
    id[12] = (employeeNum / 10) % 10 + '0';
    id[13] = employeeNum % 10 + '0';

    // Null-terminate
    id[14] = '\0';
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
        case chief: newDoc->maxPatients = 5; break;     // Chief handles urgence only
        case president: newDoc->maxPatients = 3; break; // President handles special cases
        default:;//;
    }
    initId(newDoc->id, name, age, rank, employeNum);
    doctors[employeNum] = newDoc;  // Store pointer in array
    //addDocToDepa(newDoc);
    if (newDoc->department == 0) {
        rootEmeDoc = insertTree(rootEmeDoc, newDoc,newDoc->id, rank,firstInsert,flip);
        *firstInsert=1;
    } else if (newDoc->department == 1) {
        rootCarDoc = insertTree( rootCarDoc,newDoc, newDoc->id, rank,firstInsert,flip);
        *firstInsert=1;
    } else if (newDoc->department == 2) {
        rootPhyDoc = insertTree(rootPhyDoc, newDoc,newDoc->id, rank,firstInsert,flip);
        *firstInsert=1;    
    } ;
    employeNum++;
    printf("doctor Id is %s\n",newDoc->id);
}

/*doctor* assignDoc(patient *patient){
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

}*/

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
doctor* findDocById(char id[14],rank searchRank) {
    doctor* foundNode = NULL;
    if (rootEmeDoc != NULL) {
        foundNode = search(rootEmeDoc, id, searchRank, firstSearch);
    }
    if (foundNode == NULL && rootCarDoc != NULL) {
        foundNode = search(rootCarDoc, id, searchRank, firstSearch);
    }
    if (foundNode == NULL && rootPhyDoc != NULL) {
        foundNode = search(rootPhyDoc, id, searchRank, firstSearch);
    }
    return foundNode;

}
void deleteDoc(char id[14], department searchDepartment, rank searchRank) {
    TreeNode* foundNode = NULL;
    if (searchDepartment == 0) {
        rootEmeDoc = deleteNode(rootEmeDoc, id, searchRank, firstSearch);
    } else if (searchDepartment == 1) {
        rootCarDoc = deleteNode(rootCarDoc, id, searchRank, firstSearch);
    } else if (searchDepartment == 2) {
        rootPhyDoc = deleteNode(rootPhyDoc, id, searchRank, firstSearch);
    }
}
const char *rankToString(rank rank) {
    switch (rank) {
        case intern:    return "intern";
        case low:       return "low";
        case med:       return "medium";
        case high:      return "high";
        case chief:     return "chief";
        case president: return "president";
        default:        return "unknown";
    }
}

void viewAllDoctors(){
    printf("1-view only names\n-2view names and ids");
    int choice;
    scanf("%d", &choice);
    if (choice==1)
    {
   
    for (int i = 0; i < employeNum; i++)
    {
        printf("-The doctor number %d is %s\n",i+1,doctors[i]->name);
    }}
    else if(choice==2){
        for (int i = 0; i < employeNum; i++)
        {
            printf("-The doctor number %d is %s\n his id is %s\n",i+1,doctors[i]->name,doctors[i]->id);
        }}
    ;
    //manage patients
    
}