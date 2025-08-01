#include "../headers/nav.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>  // For size_t
#include <wchar.h>   // For wchar_t and related functions
#include <stdbool.h>
#include "../headers/patients.h"
#include "../headers/doctors.h"
#include "../headers/hospital.h"
#include "../headers/queue.h"
#include "../headers/stack.h"
#include "../headers/saveLoad.h"
#include "../headers/resources.h"
#include "../headers/linked.h"


extern doctor *doctors[200];


void addPatientNav() {
    char name[30];
    int age;
    char medicalCase[200];
    char address[150];
    condition patientCondition;
    department patientDepartment;
    int conditionChoice, departmentChoice;
    bool isAssured;
    printf("\n--- Add Patient ---\n");
    while (getchar() != '\n');
    
    printf("1-Enter the patient name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; 
    
    printf("2-Enter the patient age: ");
    scanf("%d", &age);
    while (getchar() != '\n'); 
    
    printf("3-Enter the patient medical case: ");
    fgets(medicalCase, sizeof(medicalCase), stdin);
    medicalCase[strcspn(medicalCase, "\n")] = 0;
    
    printf("4-Enter the patient address: ");
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = 0;
    
    printf("5-Select patient condition:\n");
    printf("   1. Urgence\n");
    printf("   2. Danger\n");
    printf("   3. Normal\n");
    printf("   4. Visit\n");
    printf("Enter choice (1-4): ");
    scanf("%d", &conditionChoice);
    if(checkRange(conditionChoice,1,4)){
    switch(conditionChoice) {
        case 1:
            patientCondition = urgence;
            break;
        case 2:
            patientCondition = danger;
            break;
        case 3:
            patientCondition = normal;
            break;
        case 4:
            patientCondition = visit;
            break;
    }}else{
        printf("wrong choice \n");
        homePage();
    }
    
    while (getchar() != '\n'); 
    
    printf("6-Select patient department:\n");
    printf("   1. Lab\n");
    printf("   2. Cardiology\n");
    printf("   3. Physiology\n");
    printf("   4. neurology\n");
    printf("Enter choice (1-4): ");
    scanf("%d", &departmentChoice);
        if(checkRange(departmentChoice,1,4)){

    switch(departmentChoice) {
        case 1:
            patientDepartment = lab;
            break;
        case 2:
            patientDepartment = cardiology;
            break;
        case 3:
            patientDepartment = physiology;
            break;
        case 4:
            patientDepartment = neurology;
            break;
    }}else{
        printf("wrong choice \n");
        homePage();
    }
    printf("7-does the client have assurance plan ?:\n");
    printf("   1. Yes\n");
    printf("   2. No\n");
    scanf("%d",&isAssured);
    addPatient(name, age, medicalCase, address, patientCondition, patientDepartment,isAssured);
    
}
void editPatientNav() {
    int editChoice;
    char name[30];
    int age;
    char medicalCase[200];
    char address[150];
    condition patientCondition;
    department patientDepartment;
    int conditionChoice, departmentChoice;
    
    printf("enter id of patient you want to edit\n and his condition \n ");
    char id[15];
    int ch;
while ((ch = getchar()) != '\n' && ch != EOF); // flush stdin

    fgets(id, sizeof(id), stdin);
    
    // Remove newline if present
    size_t len = strlen(id);
    if (len > 0 && id[len - 1] == '\n') {
        id[len - 1] = '\0';
    }
    condition searchCondition;
    scanf("%d", &searchCondition);
    

    //find patient
    patient *patient = findPatientById(id,searchCondition);
    if (patient->id == NULL) {
        printf("No patient found with ID: %s\n", id);
        return;
    }
    
    // Display the edit menu
    printf("\n--- Edit Patient Information ---\n");
    printf("1. Edit Name\n");
    printf("2. Edit Age\n");
    printf("3. Edit Medical Case\n");
    printf("4. Edit Address\n");
    printf("5. Edit Condition\n");
    printf("6. Edit Department\n");
    printf("7. Edit All Information\n");
    printf("0. Cancel\n");
    printf("Enter your choice: ");
    scanf("%d", &editChoice);
    while (getchar() != '\n'); // Clear input buffer
    
    switch(editChoice) {
        case 0:
            printf("Edit cancelled.\n");
            return;
            
        case 1: // Edit Name
            printf("Enter new name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;
            updatePatientName(patient, name);
            break;
            
        case 2: // Edit Age
            printf("Enter new age: ");
            scanf("%d", &age);
            while (getchar() != '\n');
            updatePatientAge(patient, age);
            break;
            
        case 3: // Edit Medical Case
            printf("Enter new medical case: ");
            fgets(medicalCase, sizeof(medicalCase), stdin);
            medicalCase[strcspn(medicalCase, "\n")] = 0;
            updatePatientMedicalCase(patient, medicalCase);
            break;
            
        case 4: // Edit Address
            printf("Enter new address: ");
            fgets(address, sizeof(address), stdin);
            address[strcspn(address, "\n")] = 0;
            updatePatientAddress(patient, address);
            break;
            
        case 5: // Edit Condition
            printf("Select new patient condition:\n");
            printf("   1. Urgence\n");
            printf("   2. Danger\n");
            printf("   3. Normal\n");
            printf("   4. Visit\n");
            printf("Enter choice (1-4): ");
            scanf("%d", &conditionChoice);
            while (getchar() != '\n');
         if(checkRange(conditionChoice,1,4)){
            switch(conditionChoice) {
                case 1: patientCondition = urgence; break;
                case 2: patientCondition = danger; break;
                case 3: patientCondition = normal; break;
                case 4: patientCondition = visit; break;
                default:
                    patientCondition = normal; 
                    printf("Invalid choice, setting to Normal.\n");
            }
            updatePatientCondition(patient, patientCondition,patient->department);
            break;}else{

                  printf("wrong choice \n");
        homePage();
            }
            
        case 6: // Edit Department
            printf("Select new patient department:\n");
            printf("   1. Lab\n");
            printf("   2. Cardiology\n");
            printf("   3. Physiology\n");
            printf("   4. neurology\n");
            printf("Enter choice (1-4): ");
            scanf("%d", &departmentChoice);
            while (getchar() != '\n');
             if(checkRange(departmentChoice,1,4)){
            switch(departmentChoice) {
                case 1: patientDepartment = lab; break;
                case 2: patientDepartment = cardiology; break;
                case 3: patientDepartment = physiology; break;
                case 4: patientDepartment = neurology; break;
            }
            updatePatientDepartment(patient, patientDepartment);
            break;}else{
        printf("wrong choice \n");
        homePage();
}
            
        case 7: // Edit All Information
            printf("Enter new name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;
            
            printf("Enter new age: ");
            scanf("%d", &age);
            while (getchar() != '\n');
            
            printf("Enter new medical case: ");
            fgets(medicalCase, sizeof(medicalCase), stdin);
            medicalCase[strcspn(medicalCase, "\n")] = 0;
            
            printf("Enter new address: ");
            fgets(address, sizeof(address), stdin);
            address[strcspn(address, "\n")] = 0;
            
            printf("Select new patient condition:\n");
            printf("   1. Urgence\n");
            printf("   2. Danger\n");
            printf("   3. Normal\n");
            printf("   4. Visit\n");
            printf("Enter choice (1-4): ");
            scanf("%d", &conditionChoice);
            while (getchar() != '\n');
            if(checkRange(conditionChoice,1,4)){
            switch(conditionChoice) {
                case 1: patientCondition = urgence; break;
                case 2: patientCondition = danger; break;
                case 3: patientCondition = normal; break;
                case 4: patientCondition = visit; break;
            }}else{
        printf("wrong choice \n");
        homePage();
}
            
            printf("Select new patient department:\n");
            printf("   1. Lab\n");
            printf("   2. Cardiology\n");
            printf("   3. Physiology\n");
            printf("   4. neurology\n");
            printf("Enter choice (1-4): ");
            scanf("%d", &departmentChoice);
            while (getchar() != '\n');
            if(checkRange(departmentChoice,1,4)){
            switch(departmentChoice) {
                case 1: patientDepartment = lab; break;
                case 2: patientDepartment = cardiology; break;
                case 3: patientDepartment = physiology; break;
                case 4: patientDepartment = neurology; break;
                default:
                    patientDepartment = neurology;
                    printf("Invalid choice, setting to neurology.\n");
            }}
            else{
        printf("wrong choice \n");
        homePage();
}
            // Update all patient information at once
            updatePatient(patient, name, age, medicalCase, address, patientCondition, patientDepartment);
            break;
            
        default:
            printf("Invalid choice.\n");
            editPatientNav();
            return;
    }
    
    printf("Patient information updated successfully!\n");
}
void deletePatientNav(){
    printf("enter id of patient you want to delete\n and his condition \n and his department\n");
    char id[15];
    int ch;
while ((ch = getchar()) != '\n' && ch != EOF); // flush stdin

    fgets(id, sizeof(id), stdin);
    
    // Remove newline if present
    size_t len = strlen(id);
    if (len > 0 && id[len - 1] == '\n') {
        id[len - 1] = '\0';};
    condition deleteCondition;
    if(checkRange(deleteCondition,1,4)){
    scanf("%d", &deleteCondition);}else{
        printf("wrong choice \n");
        homePage();
    }
    department deleteDepartment;
        if(checkRange(deleteCondition,1,4)){
    scanf("%d", &deleteDepartment);  }
    else{
        printf("wrong choice \n");
        homePage();
    }

    deletePat(id,deleteCondition,deleteDepartment);
};
void viewPatientNav(){
    printf("enter id of patient you want to view\n and his condition \n ");
    char id[15];
    int ch;
while ((ch = getchar()) != '\n' && ch != EOF); 

    fgets(id, sizeof(id), stdin);
    size_t len = strlen(id);
    if (len > 0 && id[len - 1] == '\n') {
        id[len - 1] = '\0';
    }
    condition searchCondition;
    scanf("%d", &searchCondition);

    patient *patient = findPatientById(id,searchCondition);
    if (patient->id == NULL) {
        printf("No patient found with ID: %s\n", id);
        return;
    }
    printf("\n--- Patient Details ---\n");
    printf("Name: %s\n", patient->name);
    printf("Age: %d\n", patient->age);
    printf("Medical Case: %s\n", patient->medicalCase);
    printf("Address: %s\n", patient->address);
    printf("Condition: %s\n", conditionToString(patient->condition));
    printf("Department: %s\n", departmentToString(patient->department));
    printf("-----------------------\n");

};


void addDoctorNav() {
    char name[30];
    int age;
    char specialty[100];
    char address[150];
    rank doctorRank;
    department departmentDoc;
    int rankChoice;

    printf("\n--- Add Doctor ---\n");
    while (getchar() != '\n'); 

    printf("1-Enter the doctor name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("2-Enter the doctor age: ");
    scanf("%d", &age);
    while (getchar() != '\n');
    if (age<18||age>101)
    {
        printf("error\n");
        homePage();
    }
    

    printf("3-Enter the doctor specialty: ");
    fgets(specialty, sizeof(specialty), stdin);
    specialty[strcspn(specialty, "\n")] = 0;

    printf("4-Enter the doctor address: ");
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = 0;

    printf("5-Select doctor rank:\n");
    printf("   1. Intern\n");
    printf("   2. Low\n");
    printf("   3. Medium\n");
    printf("   4. High\n");
    printf("   5. Cheif\n");
    printf("   6. President\n");
    printf("Enter choice (1-6): ");
    scanf("%d", &rankChoice);
    printf("6-Select doctor department:\n");
    printf("   1. Lab\n");
    printf("   2. Cardiology\n");
    printf("   3. Physiology\n");
    printf("   4. neurology\n");
    printf("Enter choice (1-4): ");
    scanf("%d", &departmentDoc);
    if( checkPositionAvailibility( rankChoice, departmentDoc)){
    switch(rankChoice) {
        case 1:
            doctorRank = intern;
            break;
        case 2:
            doctorRank = low;
            break;
        case 3:
            doctorRank = med;
            break;
        case 4:
            doctorRank = high;
            break;
        case 5:
            doctorRank = chief;
            break;
        case 6:
            doctorRank = president;
            break;
        default:
            doctorRank = intern; 
            printf("Invalid choice, setting to Intern.\n");
    }
    addDoctor(name, age, specialty, address, doctorRank,departmentDoc);}
    else{
        printf("there is no available position for this doctor\n");
    }

   
}

void deleteDoctorNav() {
    char id[15];
    rank deleteRank;
    department deleteDepartment;

    // Clear stdin before starting input
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    // Prompt and read ID
    printf("Enter the ID of the doctor to delete: ");
    fgets(id, sizeof(id), stdin);

    // Remove newline if present
    size_t len = strlen(id);
    if (len > 0 && id[len - 1] == '\n') {
        id[len - 1] = '\0';
    }

    // Prompt and read rank and department
    printf("Enter the doctor's rank (as an integer): ");
    scanf("%d", &deleteRank);

    printf("Enter the doctor's department (as an integer): ");
    scanf("%d", &deleteDepartment);

    // Call deletion function
    deleteDoc(id, deleteDepartment, deleteRank);
}

void viewDoctorNav() {
    printf("Enter the ID of the doctor you want to view\n");

    char id[15];
    int ch;
while ((ch = getchar()) != '\n' && ch != EOF);

    fgets(id, sizeof(id), stdin);
    
    size_t len = strlen(id);
    if (len > 0 && id[len - 1] == '\n') {
        id[len - 1] = '\0';}

    rank searchRank;
    scanf("%d", &searchRank);

   

    // Find doctor
    doctor *doc = findDocById(id, searchRank);
    if (doc == NULL || doc->id == NULL) {
        printf("No doctor found with ID: %s\n", id);
        return;
    }

    printf("\n--- Doctor Details ---\n");
    printf("Name: %s\n", doc->name);
    printf("Age: %d\n", doc->age);
    printf("Specialty: %s\n", doc->speciality);
    printf("Address: %s\n", doc->address);
    printf("Rank: %s\n", rankToString(doc->rank)); 
    printf("Department: %s\n", departmentToString(doc->department));
    printf("----------------------\n");
}
void editDoctorNav() {
    int editChoice;
    char name[30];
    int age;
    char specialty[200];
    char address[150];
    rank doctorRank;
    department doctorDepartment;
    int rankChoice, departmentChoice;
    char id[15];

    printf("Enter rank (1-6): ");
    if (scanf("%d", &rankChoice) != 1 || rankChoice < 1 || rankChoice > 6) {
        printf("Invalid rank entered.\n");
        return;
    }

    rank searchRank = (rank)rankChoice;

    // Flush stdin before using fgets
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    // Ask for ID
    printf("Enter ID of doctor you want to edit: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0';

    // Now search
    doctor *doctor = findDocById(id, searchRank);
    if (doctor == NULL || doctor->id == NULL) {
        printf("No doctor found with ID: %s and Rank: %d\n", id, rankChoice);
        return;
    }

    
   
    

    // Display the edit menu
    printf("\n--- Edit Doctor Information ---\n");
    printf("1. Edit Name\n");
    printf("2. Edit Age\n");
    printf("3. Edit Specialty\n");
    printf("4. Edit Address\n");
    printf("5. Edit Rank\n");
    printf("6. Edit Department\n");
    printf("7. Edit All Information\n");
    printf("0. Cancel\n");
    printf("Enter your choice: ");
    scanf("%d", &editChoice);
    while (getchar() != '\n');

    switch (editChoice) {
        case 0:
            printf("Edit cancelled.\n");
            return;

        case 1:
            printf("Enter new name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;
            updateDoctorName(doctor, name);
            break;

        case 2:
            printf("Enter new age: ");
            scanf("%d", &age);
            while (getchar() != '\n');
            updateDoctorAge(doctor, age);
            break;

        case 3:
            printf("Enter new specialty: ");
            fgets(specialty, sizeof(specialty), stdin);
            specialty[strcspn(specialty, "\n")] = 0;
            updateDoctorSpecialty(doctor, specialty);
            break;

        case 4:
            printf("Enter new address: ");
            fgets(address, sizeof(address), stdin);
            address[strcspn(address, "\n")] = 0;
            updateDoctorAddress(doctor, address);
            break;

        case 5:
            printf("Select new doctor rank:\n");
            printf("   1. Intern\n");
            printf("   2. low\n");
            printf("   3. Medium\n");
            printf("   4. High\n");
            printf("   5. chief\n");
            printf("   6. President\n");

            printf("Enter choice (1-6): ");
            scanf("%d", &rankChoice);
            while (getchar() != '\n');
            
            if( checkPositionAvailibility( rankChoice, doctor->department)){
            switch (rankChoice) {
                case 1: doctorRank = intern; break;
                case 2: doctorRank = low; break;
                case 3: doctorRank = med; break;
                case 4: doctorRank = high; break;
                case 5: doctorRank = chief; break;
                case 6: doctorRank = president; break;


                default:
                    doctorRank = med;
                    printf("Invalid choice, setting to med.\n");
            }

          

            updateDoctorRank(doctor, doctorRank,  doctor->department);
            break;}
            else{
                printf("the position is not available\n");
                break;
            }

        case 6:
            printf("Select new doctor department:\n");
            printf("   1. Lab\n");
            printf("   2. Cardiology\n");
            printf("   3. Physiology\n");
            printf("   4. neurology\n");
            printf("Enter choice (1-4): ");
            scanf("%d", &departmentChoice);
            while (getchar() != '\n');
            if( checkPositionAvailibility( doctor->rank, departmentChoice)){
            switch (departmentChoice) {
                case 1: doctorDepartment = lab; break;
                case 2: doctorDepartment = cardiology; break;
                case 3: doctorDepartment = physiology; break;
                case 4: doctorDepartment = neurology; break;
                default:
                    doctorDepartment = neurology;
                    printf("Invalid choice, setting to neurology.\n");
            }

            updateDoctorDepartment(doctor, doctorDepartment);
            break;}else{
                printf("the position is not available in selected department\n");
                break;
            }

            case 7:
            printf("Enter new name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;
        
            printf("Enter new age: ");
            scanf("%d", &age);
            while (getchar() != '\n');
        
            printf("Enter new specialty: ");
            fgets(specialty, sizeof(specialty), stdin);
            specialty[strcspn(specialty, "\n")] = 0;
        
            printf("Enter new address: ");
            fgets(address, sizeof(address), stdin);
            address[strcspn(address, "\n")] = 0;
        
            printf("Select new doctor rank:\n");
            printf("   1. Intern\n");
            printf("   2. Low\n");
            printf("   3. Medium\n");
            printf("   4. High\n");
            printf("   5. Chief\n");
            printf("   6. President\n");
            printf("Enter choice (1-6): ");
            scanf("%d", &rankChoice);
            while (getchar() != '\n');
        
            switch (rankChoice) {
                case 1: doctorRank = intern; break;
                case 2: doctorRank = low; break;
                case 3: doctorRank = med; break;
                case 4: doctorRank = high; break;
                case 5: doctorRank = chief; break;
                case 6: doctorRank = president; break;
                default:
                    printf("Invalid rank choice.\n");
                    return;
            }
        
            printf("Select new doctor department:\n");
            printf("   1. Lab\n");
            printf("   2. Cardiology\n");
            printf("   3. Physiology\n");
            printf("   4. neurology\n");
            printf("Enter choice (1-4): ");
            scanf("%d", &departmentChoice);
            while (getchar() != '\n');
        
            switch (departmentChoice) {
                case 1: doctorDepartment = lab; break;
                case 2: doctorDepartment = cardiology; break;
                case 3: doctorDepartment = physiology; break;
                case 4: doctorDepartment = neurology; break;
                default:
                    printf("Invalid department choice.\n");
                    return;
            }
        
            if (checkPositionAvailibility(doctorRank, doctorDepartment)) {
                updateDoctor(doctor, name, age, specialty, address, doctorRank, doctorDepartment);
            } else {
                printf("The position is not available in the selected department.\n");
            }
            break;
        

        default:
            printf("Invalid choice.\n");
            editDoctorNav();
            return;
    }

    
}

void dischargePatient(stack **top){
    int subChoice;
    printf("1 - Find patient by ID and condition\n");
    printf("2 - Find patient by name\n");
    printf("0 - Go back\n");
    printf("Choose an option: ");
    scanf("%d", &subChoice);

    if (subChoice == 0) {
        homePage();
        return;
    }

    char id[15], name[30];
    condition condChoice;
    patient *pat = NULL;

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF); 

    if (subChoice == 1) {
        printf("Enter condition (1-4): ");
        if (scanf("%d", &condChoice) != 1 || condChoice < 1 || condChoice > 6) {
            printf("Invalid condition entered.\n");
            return;
        }

        while ((ch = getchar()) != '\n' && ch != EOF); // flush

        printf("Enter ID of patient you want to find: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = '\0';

         pat= findPatientById(id, condChoice);
        if (pat == NULL) {
            printf("No patient found with ID %s and condition %d\n", id, condChoice);
            return;
        }
    } else if (subChoice == 2) {
        printf("Enter patient name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        extern patient *patients[];
        extern int patientNum;

        for (int i = 0; i < patientNum; i++) {
            if (strcmp(patients[i]->name, name) == 0) {
                pat = patients[i];
                break;
            }
        }

        if (pat == NULL) {
            printf("No patient found with name: %s\n", name);
            return;
        }
    }
    
    push(top, pat); // pass pointer to pointer
    //discharge patient
};
void undoLastDischarge(stack **top){
    if (top==NULL)
    {
        printf("there is no patient to undo \n");
        homePage();
    }
    pop(top);
};
void manageDoctors() {
    printf("\n--- Doctor Management ---\n");
    printf("1. Add Doctor\n");
    printf("2. Edit Doctor\n");
    printf("3. View Doctor\n");
    printf("4. Delete Doctor\n");
    printf("5. View All Doctors\n");
    printf("6. view doctor all patients\n");
    printf("7. Back\n");
    printf("Choose an option: ");
    
    int choice;
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        addDoctorNav();
        break;
   case 2:
        editDoctorNav();
        break; 
    case 3:
        viewDoctorNav();
        break;
    case 4:
        deleteDoctorNav();
        break;
    case 5:
        viewAllDoctors();
        break;
    case 6:

        viewDocAllPatients(); 
        break;
    case 7:
        homePage(); 
        break;
    default:
        printf("Invalid option!\n");
        exit(-1);
        break;
    }
}
void managePatients() {
    printf("\n--- Patient Management ---\n");
    printf("1. Add Patient\n");
    printf("2. Edit Patient\n");
    printf("3. View Patient\n");
    printf("4. Delete Patient\n");
    printf("5. View All Patients\n");
    printf("6. Back\n");
    printf("Choose an option: ");
    
    int choice;
    scanf("%d", &choice);
    
    switch (choice) {
    case 1:
        addPatientNav();
        break;
    case 2:
        editPatientNav();
        break;
    case 3:
        viewPatientNav();
        break;
    case 4:
        deletePatientNav();
        break;
    case 5:
        viewAllPatients();
        break;
    case 6:
        homePage();  // Return to main menu
        break;
    default:
         printf("Invalid option!\n");
        exit(-1);//prevent infinite loop 
        break;
    }

 }
 void manageSessionsNav(stack **top) {
    int choice;
    printf("\n--- Session Management ---\n");
    printf("1 - Declare end of session\n");
    printf("2 - See doctor schedules\n");
    printf("0 - Go back\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    if (choice == 0) {
        homePage();
        return;
    }

    if (choice == 1 || choice == 2) {
        int subChoice;
        printf("1 - Find doctor by ID and rank\n");
        printf("2 - Find doctor by name\n");
        printf("0 - Go back\n");
        printf("Choose an option: ");
        scanf("%d", &subChoice);

        if (subChoice == 0) {
            homePage();
            return;
        }

        char id[15], name[30];
        rank rankChoice;
        doctor *doc = NULL;

        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF); // flush stdin

        if (subChoice == 1) {
            printf("Enter rank (1-6): ");
            if (scanf("%d", &rankChoice) != 1 || rankChoice < 1 || rankChoice > 6) {
                printf("Invalid rank entered.\n");
                return;
            }

            while ((ch = getchar()) != '\n' && ch != EOF); // flush

            printf("Enter ID of doctor you want to find: ");
            fgets(id, sizeof(id), stdin);
            id[strcspn(id, "\n")] = '\0';

            doc = findDocById(id, rankChoice);
            if (doc == NULL) {
                printf("No doctor found with ID %s and rank %d\n", id, rankChoice);
                return;
            }
        } else if (subChoice == 2) {
            printf("Enter doctor name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;

            extern doctor *doctors[];
            extern int employeNum;

            for (int i = 0; i < employeNum; i++) {
                if (strcmp(doctors[i]->name, name) == 0) {
                    doc = doctors[i];
                    break;
                }
            }

            if (doc == NULL) {
                printf("No doctor found with name: %s\n", name);
                return;
            }
        }else{
            printf("Invalid choice.\n");
            exit(-1);
        }

        if (choice == 1) {
            // Declare end of session
            printf("Ending session for doctor: %s\n", doc->name);
            patient *p = dequeue(doc->doctorQueue); 
            deleteList(&(doc->patientsHead),p);
            
            if (p != NULL) {
               
                printf("what is the next decision for the patient %s :\n 1\\ discharge \n 2\\ edit the patient condition \n 3\\ have another appointment \n 4\\ send to another hospital \n",p->name);
                int decision;
                scanf("%d",&decision);
                switch (decision)
                {
                case 1:
                push(top, p);
                    break;
                case 2:
                condition patientCondition;
                int conditionChoice;
                printf("Select new patient condition:\n");
                printf("   1. Urgence\n");
                printf("   2. Danger\n");
                printf("   3. Normal\n");
                printf("   4. Visit\n");
                printf("Enter choice (1-4): ");
                scanf("%d", &conditionChoice);
                while (getchar() != '\n');
             
                switch(conditionChoice) {
                    case 1: patientCondition = urgence; break;
                    case 2: patientCondition = danger; break;
                    case 3: patientCondition = normal; break;
                    case 4: patientCondition = visit; break;
                    default:
                        patientCondition = normal; 
                        printf("Invalid choice, setting to Normal.\n");
                }
                updatePatientCondition(p, patientCondition,p->department);
                        break; 
                case 3:
                    printf("patient %s has another appointment with doctor %s\n",p->name,p->assignedDoc->name);
                    enqueue(doc->doctorQueue,p,p->assignedDoc);
                    insertList(&(doc->patientsHead), p);
                break;
                case 4:
                    printf("patient %s is sent to another hospital\n",p->name);
                    free(p);
                    deletePat(p->id,p->condition,p->department);
                    break;
                default:
                printf("invalid decision\n");
                    free(p);
                    break;
                }
                
            }
        } else {
            printf("Doctor schedule for %s:\n", doc->name);
            printf("Total patients: %d\n", doc->numPatients);
            displayDoctorSchedule(doc->doctorQueue); 
        }
    } else {
        printf("Invalid choice.\n");
        homePage();
    }
}
void viewWaitingQueue(){
    doctor *doc =NULL;
    int i=0;
    while (i<employeNum)
    {
        doc=doctors[i];
        printf("the doctor %s has %d patients and his queue is : \n",doc->name,doc->numPatients);
        displayDoctorSchedule(doc->doctorQueue);
        i++;
    }
    
};
void patientRepoNav(){
    int choice;
    
    printf("\n=== PATIENT REPORT GENERATOR ===\n");
    printf("1. Generate All Patients Report\n");
    printf("2. Generate Single Patient Report\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            generateRepo();
            break;
        case 2:
            generateOneRepo();
            break;
        case 3:
            printf("Returning to main menu...\n");
            break;
        default:
            printf("Invalid choice!\n");
            exit(-1);
        }
};

 void homePage() {

    stack *top = NULL;

    createStack(&top); // if you have a meaningful createQueue

    while (1)
    {
    printf("Choose an option:\n");
    printf("1. Manage Patients\n");
    printf("2. Manage Doctors\n");
    printf("3. Discharge Patient\n");
    printf("4. View Waiting Queue\n");
    printf("5. Manage Sessions\n");
    printf("6. Undo Last Discharge\n");
    printf("7. View Hospital Structure Tree\n");
    printf("8.Save Data to File\n");
    printf("9. Load Data from File\n");
     printf("10.Generate reports\n");
    printf("11. Exit\n");
    int n;
    scanf("%d",&n);
    switch (n)
    {
    case 1:
        managePatients();
        break;
    case 2:
        manageDoctors();
        break;
    case 3:
        dischargePatient(&top);
        break;
   case 4:
        viewWaitingQueue();
        break;
    case 5:
        manageSessionsNav(&top);
        break;
    case 6:
        undoLastDischarge(&top);
        break;
   
    case 7:
    showHospitalStructureNav();
        break;
    case 8:
        saveAllData();
        break;
    case 9:
        loadAllData();
        break;
    case 11:
        exit(0);
        break;
        case 10:
        patientRepoNav();
        break;
    default:
        printf("Invalid option!\n");
        exit(-1);
    }}
}



