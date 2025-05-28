#include "../headers/doctors.h"
#include "../headers/treeDoc.h"
#include "../headers/departments.h"
#include "../headers/queue.h"
#include "../headers/linked.h"



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
TreeNode *rootEmeDoc=NULL;
TreeNode *rootCarDoc=NULL;
TreeNode *rootPhyDoc=NULL;
TreeNode *rootNeuDoc=NULL;
int n=0;
int *firstInsert=&n;
int f=0;
int *flip=&f;
int g=0;
int *firstSearch=&g;
extern departmentInfo departments[4];

int employeNum = 0; 
doctor* doctors[200];  // Array of pointers to doctor structs

#include <stdio.h>
#include <string.h>

void initId(char id[15], const char name[30], int age, rank rankValue, int employeeNum) {
    for (int i = 0; i < 5; i++) {
        id[i] = (name[i] != '\0') ? name[i] : '_';
    }
    id[5] = (age / 100) % 10 + '0';
    id[6] = (age / 10) % 10 + '0';
    id[7] = age % 10 + '0';
    id[8] = rankValue + '0';
    id[9]  = (employeeNum / 10000) % 10 + '0';
    id[10] = (employeeNum / 1000) % 10 + '0';
    id[11] = (employeeNum / 100) % 10 + '0';
    id[12] = (employeeNum / 10) % 10 + '0';
    id[13] = employeeNum % 10 + '0';
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
    newDoc->numPatients = 0;
    switch(rank) {
        case intern: newDoc->maxPatients = 2; break;    // Interns handle visit cases only
        case low: newDoc->maxPatients = 8; break;       // Low handles visit and normal
        case med: newDoc->maxPatients = 14; break;      // Med handles all except urgence
        case high: newDoc->maxPatients = 10; break;     // High handles danger and urgence
        case chief: newDoc->maxPatients = 5; break;     // Chief handles urgence only
        case president: newDoc->maxPatients = 3; break; // President handles special cases
        default:;//;
    }
    newDoc->wage=wage(newDoc);
    initId(newDoc->id, name, age, rank, employeNum);
    doctors[employeNum] = newDoc;  // Store pointer in array
    addDocToDepa(newDoc);
    if (newDoc->department == 1) {
        rootEmeDoc = insertTree(rootEmeDoc, newDoc,newDoc->id, rank,firstInsert,flip);
        *firstInsert=1;
    } else if (newDoc->department == 2) {
        rootCarDoc = insertTree( rootCarDoc,newDoc, newDoc->id, rank,firstInsert,flip);
        *firstInsert=1;
    } else if (newDoc->department == 2) {
        rootPhyDoc = insertTree(rootPhyDoc, newDoc,newDoc->id, rank,firstInsert,flip);
        *firstInsert=1;    
    } 
    else if (newDoc->department == 4) {
        rootNeuDoc = insertTree(rootPhyDoc, newDoc,newDoc->id, rank,firstInsert,flip);
        *firstInsert=1;    
    } ;
    employeNum++;
    printf("doctor Id is %s\n",newDoc->id);
    Queue *doctorQueue = (Queue*)malloc(sizeof(Queue));
    if (doctorQueue == NULL) {
        printf("Failed to create queue\n");
        return;
    }
    newDoc->doctorQueue = doctorQueue;
    createQueue(doctorQueue);
        departments[newDoc->department-1].expenses+=newDoc->wage;
    departments[newDoc->department-1].balence-=newDoc->wage;
    newDoc->patientsHead = NULL;
}

doctor* assignDoc(patient *patient){
    doctor *assignedDoc=NULL;
    int i=0;
    switch (patient->condition)
    {
    case 1 :
        //find doctor cheif or high (Danger)
        i=0;
        while (i<employeNum)
        {
            if ((doctors[i]->rank==chief || doctors[i]->rank==high) && (doctors[i]->department==patient->department))
            {
                if (maxPatientsCheck(*doctors[i])==1)
                {
                    assignedDoc=doctors[i];
                    break;
                }
            }
           
            i++;
        }
          if (assignedDoc==NULL)
          {
            return NULL;
        }else{
            printf("doctor %s is assigned to patient %s\n",assignedDoc->name,patient->name);
            assignedDoc->numPatients++;
            patient->assignedDoc=assignedDoc;
            enqueue(assignedDoc->doctorQueue,patient,assignedDoc);
            insertList(&(assignedDoc->patientsHead), patient);

            return assignedDoc;
          }    

        break;
    case 2:
        //find doctor normal or low or  (high case)
        i=0;
        while (i<employeNum)
        {
            if ((doctors[i]->rank==med || doctors[i]->rank==high) && (doctors[i]->department==patient->department))
            {
                if (maxPatientsCheck(*doctors[i])==1)
                {
                    assignedDoc=doctors[i];
                    break;
                }
            }
          
            i++;
        }
        if (assignedDoc==NULL)
        {
          return NULL;
      }else{
          printf("doctor %s is assigned to patient %s\n",assignedDoc->name,patient->name);
          assignedDoc->numPatients++;
          patient->assignedDoc=assignedDoc;
          enqueue(assignedDoc->doctorQueue,patient,assignedDoc);
          insertList(&(assignedDoc->patientsHead), patient);

          return assignedDoc;
        }    

        break;
    case 3:
        //find doctor normal or intern (normal)
        i=0;
        while (i<employeNum)
        {
            if ((doctors[i]->rank==low || doctors[i]->rank==med) && (doctors[i]->department==patient->department))
            {
                if (maxPatientsCheck(*doctors[i])==1)
                {
                    assignedDoc=doctors[i];
                    break;
                }
            }
          
            i++;
        }
        if (assignedDoc==NULL)
        {
          return NULL;
      }else{
          printf("doctor %s is assigned to patient %s\n",assignedDoc->name,patient->name);
          assignedDoc->numPatients++;
          patient->assignedDoc=assignedDoc;
          enqueue(assignedDoc->doctorQueue,patient,assignedDoc);
          insertList(&(assignedDoc->patientsHead), patient);

          return assignedDoc;
        }    

        break;
        case 4:
        //find doctor normal or intern (normal)
        i=0;
        while (i<employeNum)
        {
            if ((doctors[i]->rank==low || doctors[i]->rank==med ||doctors[i]->rank==intern) && (doctors[i]->department==patient->department))
            {
                if (maxPatientsCheck(*doctors[i])==1)
                {
                    assignedDoc=doctors[i];
                    break;
                }
            }
          
            i++;
        }
        if (assignedDoc==NULL)
        {
          return NULL;
      }else{
          printf("doctor %s is assigned to patient %s\n",assignedDoc->name,patient->name);
          assignedDoc->numPatients++;
          patient->assignedDoc=assignedDoc;
          enqueue(assignedDoc->doctorQueue,patient,assignedDoc);
          insertList(&(assignedDoc->patientsHead), patient);
          return assignedDoc;
        }    

        break;
    default:
        break;
    }
   

}

int maxPatientsCheck(doctor doctor) {

     return (doctor.numPatients < doctor.maxPatients) ? 1 : 0; // visit only cases
   

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
     if (foundNode == NULL && rootNeuDoc != NULL) {
        foundNode = search(rootNeuDoc, id, searchRank, firstSearch);
    }
    return foundNode;

}
void deleteDoc(char id[14], department searchDepartment, rank searchRank) {
    doctor *doc = NULL;
    for (int i = 0; i < employeNum; i++) {
        if (strcmp(doctors[i]->id, id) == 0) {
            doc = doctors[i];
            break;
        }
    }
    if (searchDepartment == 1) {
        rootEmeDoc = deleteNode(rootEmeDoc, id, searchRank, firstSearch);
    } else if (searchDepartment == 2) {
        rootCarDoc = deleteNode(rootCarDoc, id, searchRank, firstSearch);
    } else if (searchDepartment ==3) {
        rootPhyDoc = deleteNode(rootPhyDoc, id, searchRank, firstSearch);
    }else if (searchDepartment ==4) {
        rootNeuDoc = deleteNode(rootNeuDoc, id, searchRank, firstSearch);
    }
    employeNum--;
    deleteDocFromDepa(doc);
    printf("doctor deleted\n");
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
    printf("1-view only names\n-2view all info \n");
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
printf("-The doctor number %d is %s\n", i + 1, doctors[i]->name);
printf("   id : %s\n", doctors[i]->id);
printf("   age : %d\n", doctors[i]->age);
printf("   address : %s\n", doctors[i]->address);
printf("   speciality : %s\n", doctors[i]->speciality);
printf("   rank : %s\n", rankToString(doctors[i]->rank)); 
printf("   assigned to : %s department\n", departmentToString(doctors[i]->department));
printf("   has %d patients\n", doctors[i]->numPatients);
printf("   max patients capacity : %d\n", doctors[i]->maxPatients);
printf("   wage : %d\n", doctors[i]->wage);
        }}
    ;
    
}
void updateDoctorName(doctor *doctor, char name[30]) {
    strcpy(doctor->name, name);
    printf("Doctor name updated to %s\n", name);
}

void updateDoctorAge(doctor *doctor, int age) {
    doctor->age = age;
    printf("Doctor age updated to %d\n", age);
}

void updateDoctorSpecialty(doctor *doctor, char specialty[200]) {
    strcpy(doctor->speciality, specialty);
    printf("Doctor specialty updated to %s\n", specialty);
}

void updateDoctorAddress(doctor *doctor, char address[150]) {
    strcpy(doctor->address, address);
    printf("Doctor address updated to %s\n", address);
}

void updateDoctorRank(doctor *doctor, rank rank, department department) {
    deleteDoc(doctor->id, doctor->rank, doctor->department);

    doctor->rank = rank;

    if (doctor->department ==1) {
        rootEmeDoc = insertTree(rootEmeDoc, doctor, doctor->id, doctor->rank, firstInsert, flip);
        *firstInsert = 1;
    } else if (doctor->department == 2) {
        rootCarDoc = insertTree(rootCarDoc, doctor, doctor->id, doctor->rank, firstInsert, flip);
        *firstInsert = 1;
    } else if (doctor->department == 3) {
        rootPhyDoc = insertTree(rootPhyDoc, doctor, doctor->id, doctor->rank, firstInsert, flip);
        *firstInsert = 1;
    } else if (doctor->department == 4) {
        rootNeuDoc = insertTree(rootPhyDoc, doctor,doctor->id, doctor->rank,firstInsert,flip);
        *firstInsert=1;    
    } ;

    printf("Doctor rank updated to %s\n", rankToString(rank));
}

void updateDoctorDepartment(doctor *doctor, department department) {
    deleteDoc(doctor->id, doctor->rank, doctor->department);

    doctor->department = department;

     if (doctor->department ==1) {
        rootEmeDoc = insertTree(rootEmeDoc, doctor, doctor->id, doctor->rank, firstInsert, flip);
        *firstInsert = 1;
    } else if (doctor->department == 2) {
        rootCarDoc = insertTree(rootCarDoc, doctor, doctor->id, doctor->rank, firstInsert, flip);
        *firstInsert = 1;
    } else if (doctor->department == 3) {
        rootPhyDoc = insertTree(rootPhyDoc, doctor, doctor->id, doctor->rank, firstInsert, flip);
        *firstInsert = 1;
    } else if (doctor->department == 4) {
        rootNeuDoc = insertTree(rootPhyDoc, doctor,doctor->id, doctor->rank,firstInsert,flip);
        *firstInsert=1;    
    } ;

    printf("Doctor department updated to %s\n", departmentToString(department));
    addDocToDepa(doctor);
}

void updateDoctor(doctor *doctor, char name[30], int age, char specialty[200], char address[150], rank rank, department department) {
    deleteDoc(doctor->id, doctor->rank, doctor->department);

    strcpy(doctor->name, name);
    doctor->age = age;
    strcpy(doctor->speciality, specialty);
    strcpy(doctor->address, address);
    doctor->rank = rank;
    doctor->department = department;

    if (doctor->department ==1) {
        rootEmeDoc = insertTree(rootEmeDoc, doctor, doctor->id, doctor->rank, firstInsert, flip);
        *firstInsert = 1;
    } else if (doctor->department == 2) {
        rootCarDoc = insertTree(rootCarDoc, doctor, doctor->id, doctor->rank, firstInsert, flip);
        *firstInsert = 1;
    } else if (doctor->department == 3) {
        rootPhyDoc = insertTree(rootPhyDoc, doctor, doctor->id, doctor->rank, firstInsert, flip);
        *firstInsert = 1;
    } else if (doctor->department == 4) {
        rootNeuDoc = insertTree(rootPhyDoc, doctor,doctor->id, doctor->rank,firstInsert,flip);
        *firstInsert=1;    
    } ;

    printf("Doctor name updated to %s\n", name);
    printf("Doctor age updated to %d\n", age);
    printf("Doctor specialty updated to %s\n", specialty);
    printf("Doctor address updated to %s\n", address);
    printf("Doctor rank updated to %s\n", rankToString(rank));
    printf("Doctor department updated to %s\n", departmentToString(department));
    addDocToDepa(doctor);
    printf("Doctor updated successfully!\n");
}
int checkPositionAvailibility(rank rank, department department) {
    for (int i = 0; i < employeNum; i++) {
        if (doctors[i] == NULL) continue;

        if (rank == president) {
            if (doctors[i]->rank == president) {
                return 0; // Only one president allowed
            }
        } else if (rank == chief) {
            if (doctors[i]->rank == chief && doctors[i]->department == department) {
                return 0; // Only one chief per department allowed
            }
        }
    }

    return 1; // Available
}
int wage(doctor *doctor){
    switch (doctor->rank)
    {
    case 1:
        return 20;
        break;
    case 2:
        return 620;
        break;
        case 3:
        return 1000;
        break;
    case 4:
        return 1500;
        break;
    case 5:
        return 2000;
        break;
    case 6:
        return 2500;
        break;
    default:
        break;
    }

    
}
void viewDocAllPatients() {
    char name[30];

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Enter doctor name to view all his patients: ");
    if (fgets(name, sizeof(name), stdin) == NULL) {
        printf("Error reading input.\n");
        return;
    }
    name[strcspn(name, "\n")] = '\0';
    doctor *doc = NULL;
    for (int i = 0; i < employeNum; i++) {
        if (doctors[i] != NULL && strcmp(doctors[i]->name, name) == 0) {
            doc = doctors[i];
            break;
        }
    }

    if (doc == NULL) {
        printf("Doctor not found.\n");
        return;
    }

    printf("\nDoctor %s has the following patients:\n", doc->name);

    if (doc->patientsHead == NULL) {
        printf("No patients assigned to this doctor.\n");
        return;
    }

    list *current = doc->patientsHead;
    int patientCount = 1;
    
    while (current != NULL) {
        if (current->pat != NULL) {
            printf("%d. %s (Condition: %d)\n", 
                   patientCount++, 
                   current->pat->name,
                   current->pat->condition);
        } else {
            printf("%d. [Corrupted patient data]\n", patientCount++);
        }
        current = current->next;
    }
}
