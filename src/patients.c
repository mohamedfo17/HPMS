#include "../headers/patients.h"
#include "../headers/treePat.h"
#include "../headers/departments.h"
#include "../headers/doctors.h"
#include "../headers/linked.h"

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
TreeNodePat *rootNeuPat=NULL;
void addPatient(char name[30], int age, char medicalCase[200], char address[150], condition condition, department department,bool isAssured) {
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
    newPatient->isAssured=isAssured;
    newPatient->sessionCost=sessionCost(newPatient);
    initId(newPatient->id, name, age, condition, patientNum);
    int check =addPatientToDepa(newPatient);
    if(check){
        if(assignDoc(newPatient)==NULL){
        printf("no doctor available for this patient deporting to another hospital ...\n");
        departments[newPatient->department-1].numPat--;
        free(newPatient);
        return;
    }
    patients[patientNum] = newPatient;
    if (newPatient->department == 1) {
        rootEmePat = insertTreePat(rootEmePat,newPatient, newPatient->id, condition,firstInsertP,flipP);
        *firstInsertP=1;
    } else if (newPatient->department == 2) {
        rootCarPat = insertTreePat(rootCarPat,newPatient, newPatient->id, condition,firstInsertP,flipP);
        *firstInsertP=1;
    } else if (newPatient->department == 3) {
        rootPhyPat = insertTreePat(rootPhyPat,newPatient, newPatient->id, condition,firstInsertP,flipP);
        *firstInsertP=1;
    }  else if (newPatient->department == 4) {
        rootNeuPat = insertTreePat(rootNeuPat, newPatient,newPatient->id, condition,firstInsertP,flipP);
        *firstInsertP=1;    
    } ;
    patientNum++;
        printf("Patient added successfully!\n");
        printf("Patient Id is %s\n",newPatient->id);
        
    }else{
        printf("failed to add patient\n");
        free(newPatient);
    }

}

void viewAllPatients(){
    printf("1-view only names\n-2view all info");
    int choice;
    scanf("%d", &choice);
    if (choice==1)
    {
   
    for (int i = 0; i < patientNum; i++)
    {
        printf("-The patient number %d is %s\n",i+1,patients[i]->name);
    }} else if(choice==2){
        for (int i = 0; i < patientNum; i++)
    {       printf("-The patient number %d is %s\n",i+1,patients[i]->name);
            printf("   Id : %s\n",patients[i]->id);
            printf("   Age : %d\n",patients[i]->age);
            printf("   Address : %s\n",patients[i]->address);
            printf("   Doctor : %s\n",patients[i]->assignedDoc);
            printf("   Condition : %s\n",conditionToString((patients[i]->age)));
            printf("   Session cost : %d\n",patients[i]->sessionCost);
            printf("   Department : %s\n",departmentToString((patients[i]->department)));


           
            
        }}
    //manage patients
    
}
void updatePatientName(patient *patient, char name[30]) {
    strcpy(patient->name, name);
    printf("Patient name updated to %s\n", name);

}
void updatePatientAge(patient *patient, int age) {
patient->age=age;
printf("Patient age updated to %d\n", age);

}
void updatePatientMedicalCase(patient *patient,char medicalCase[200])
 {
    strcpy(patient->medicalCase, medicalCase);
    printf("Patient medical case updated to %s\n", medicalCase);

}
void updatePatientAddress(patient *patient,char address[150])
 {
    strcpy(patient->address, address);
    printf("Patient address updated to %s\n", address);

}
void updatePatientCondition(patient *patient,condition condition,department department) {
    deletePat(patient->id,patient->condition,patient->department);
   

    patient->condition = condition;
    if (patient->department == 1) {
        rootEmePat = insertTreePat(rootEmePat,patient, patient->id,patient->condition,firstInsertP,flipP);
        *firstInsertP=1;
    } else if (patient->department == 2) {
        rootCarPat = insertTreePat(rootCarPat,patient, patient->id, patient->condition,firstInsertP,flipP);
        *firstInsertP=1;
    } else if (patient->department == 3) {
        rootPhyPat = insertTreePat(rootPhyPat,patient, patient->id, patient->condition,firstInsertP,flipP);
        *firstInsertP=1;
    }  else if (patient->department == 4) {
        rootNeuPat = insertTreePat(rootNeuPat, patient,patient->id, condition,firstInsertP,flipP);
        *firstInsertP=1;    
    } ;;

    printf("Patient condition updated to %s\n", conditionToString(condition));
 if(assignDoc(patient)==NULL){
        printf("no doctor available for this patient deporting to another hospital ...\n");
                departments[patient->department-1].numPat--;

        free(patient);
        return;
    }
}
void updatePatientDepartment(patient *patient,department department) {
    deletePat(patient->id,patient->condition,patient->department);
    
    patient->department = department;
    if (patient->department == 1) {
        rootEmePat = insertTreePat(rootEmePat,patient, patient->id,patient->condition,firstInsertP,flipP);
        *firstInsertP=1;
    } else if (patient->department == 2) {
        rootCarPat = insertTreePat(rootCarPat,patient, patient->id, patient->condition,firstInsertP,flipP);
        *firstInsertP=1;
    } else if (patient->department == 3) {
        rootPhyPat = insertTreePat(rootPhyPat,patient, patient->id, patient->condition,firstInsertP,flipP);
        *firstInsertP=1;
    } else if (patient->department == 4) {
        rootNeuPat = insertTreePat(rootNeuPat, patient,patient->id, patient->condition,firstInsertP,flipP);
        *firstInsertP=1;    
    } ;
    printf("Patient department updated to %s\n", departmentToString(department));
   
    if(assignDoc(patient)==NULL){
        printf("no doctor available for this patient deporting to another hospital ...\n");
                departments[patient->department-1].numPat--;

        free(patient);
        return;
    }
    addPatientToDepa(patient);
   
}
void updatePatient(patient *patient,char name[30],int age,char medicalCase[200],char address[150],condition condition,department department) {
    deletePat(patient->id,patient->condition,patient->department);
    
    strcpy(patient->name, name);
    patient->age=age;
    strcpy(patient->medicalCase, medicalCase);
    strcpy(patient->address, address);
    patient->condition = condition;
    patient->department = department;
    if (patient->department == 1) {
        rootEmePat = insertTreePat(rootEmePat,patient, patient->id,patient->condition,firstInsertP,flipP);
        *firstInsertP=1;
    } else if (patient->department == 2) {
        rootCarPat = insertTreePat(rootCarPat,patient, patient->id, patient->condition,firstInsertP,flipP);
        *firstInsertP=1;
    } else if (patient->department == 3) {
        rootPhyPat = insertTreePat(rootPhyPat,patient, patient->id, patient->condition,firstInsertP,flipP);
        *firstInsertP=1;
    } else if (patient->department == 4) {
        rootNeuPat = insertTreePat(rootNeuPat, patient,patient->id, patient->condition,firstInsertP,flipP);
        *firstInsertP=1;    
    } ;
    if(assignDoc(patient)==NULL){
        printf("no doctor available for this patient deporting to another hospital ...\n");
                departments[patient->department-1].numPat--;

        free(patient);
        return;
    }
    printf("Patient name updated to %s\n", name);
    printf("Patient age updated to %d\n", age);
    printf("Patient medical case updated to %s\n", medicalCase);
    printf("Patient address updated to %s\n", address);
    printf("Patient condition updated to %s\n", conditionToString(condition));
    printf("Patient department updated to %s\n", departmentToString(department));
    addPatientToDepa(patient);
    printf("Patient updated successfully!\n");
}
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
     if (foundNode == NULL && rootNeuPat != NULL) {
        foundNode = searchPat(rootNeuPat, id, searchCondition, firstSearchP);
    }
    return foundNode;

}
void deletePat(char id[14],condition searchCondition,department searchDepartment) {
    patient *patient = NULL;
    for (int i = 0; i < patientNum; i++) {
        if (strcmp(patients[i]->id, id) == 0) {
            patient = patients[i];
            break;
        }
    }
    if (searchDepartment == 1) {
        rootEmePat = deleteNodePat(rootEmePat, id, searchCondition, firstSearchP);
    } else if (searchDepartment == 2) {
        rootCarPat = deleteNodePat(rootCarPat, id, searchCondition, firstSearchP);
    } else if (searchDepartment == 3) {
        rootPhyPat = deleteNodePat(rootPhyPat, id, searchCondition, firstSearchP);
    }else if (patient->department == 4) {
        rootNeuPat = deleteNodePat(rootNeuPat, id, searchCondition,firstSearchP);
        *firstSearchP=1;    
    } ;
    patientNum--;
    deletePatientFromDepa(patient);
    deleteList(&(patient->assignedDoc->patientsHead), patient);
}

int sessionCost(patient *patient){
    if (patient->condition==1||patient->condition==2)
    {
        return patient->isAssured ? 100 : 400;
      }else if (patient->condition==3||patient->condition==4)
      {
         return patient->isAssured ? 20 : 100;

      }
        
    
    
}
void generateRepo() {
    FILE *file = fopen("completed_patients_report.txt", "w");
    if (file == NULL) {
        printf("Error: Could not create report file\n");
        return;
    }
    
    fprintf(file, "     COMPLETED PATIENTS REPORT       \n");
    
    fprintf(file, "Total Patients: %d\n\n", patientNum);
    
    for (int i = 0; i < patientNum; i++) {
        patient *pat = patients[i];
        
        fprintf(file, "--- PATIENT %d ---\n", i + 1);
        fprintf(file, "ID: %s\n", pat->id);
        fprintf(file, "Name: %s\n", pat->name);
        fprintf(file, "Age: %d\n", pat->age);
        fprintf(file, "Address: %s\n", pat->address);
        fprintf(file, "Medical Case: %s\n", pat->medicalCase);
        fprintf(file, "Condition: %s\n", conditionToString(pat->condition));
        fprintf(file, "Department: %s\n", departmentToString(pat->department));
        fprintf(file, "\n");
    }
    
    fprintf(file, "           END OF REPORT             \n");
    
    fclose(file);
    printf("Report generated successfully: completed_patients_report.txt\n");
}

void generateOneRepo(){
 int ch;
    while ((ch = getchar()) != '\n' && ch != EOF); 
  
    char patientId[15];
    printf("Enter Patient ID: ");
    scanf("%s", patientId);
    
    patient *foundPatient = NULL;

    for (int i = 0; i < patientNum; i++) {
        if (strcmp(patients[i]->id, patientId) == 0) {
            foundPatient = patients[i];
            break;
        }
    }
    
    if (foundPatient == NULL) {
        printf("Patient with ID '%s' not found!\n", patientId);
        return;
    }
    
    // Create filename based on patient ID
    char filename[50];
    sprintf(filename, "patient_%s_report.txt", patientId);
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not create report file\n");
        return;
    }
        fprintf(file, "      INDIVIDUAL PATIENT REPORT      \n");
    
    fprintf(file, "--- PATIENT INFORMATION ---\n");
    fprintf(file, "ID: %s\n", foundPatient->id);
    fprintf(file, "Name: %s\n", foundPatient->name);
    fprintf(file, "Age: %d\n", foundPatient->age);
    fprintf(file, "Address: %s\n", foundPatient->address);
    fprintf(file, "\n--- MEDICAL INFORMATION ---\n");
    fprintf(file, "Medical Case: %s\n", foundPatient->medicalCase);
    fprintf(file, "Condition: %s\n", conditionToString(foundPatient->condition));
    fprintf(file, "Department: %s\n", departmentToString(foundPatient->department));
    
    fprintf(file, "           END OF REPORT             \n");
    
    fclose(file);
    printf("Patient report generated successfully: %s\n", filename);

};
