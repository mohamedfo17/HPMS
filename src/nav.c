#include "../headers/nav.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "patients.c"
 void homePage() {
    printf("Choose an option:\n");
    printf("1. Manage Patients\n");
    printf("2. Manage Doctors\n");
    printf("3. Discharge Patient\n");
    printf("4. View Waiting Queue\n");
    printf("5. Add Patient to Queue\n");
    printf("6. Undo Last Discharge\n");
    printf("7. Search Patient in Directory Tree\n");
    printf("8. View Hospital Structure Tree\n");
    printf("9. Save Data to File\n");
    printf("10. Load Data from File\n");
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
        dischargePatient();
        break;
    case 4:
        viewWaitingQueue();
        break;
    case 5:
        addPatientToQueue();
        break;
    case 6:
        undoLastDischarge();
        break;
    case 7:
        searchPatientInTree();
        break;
    case 8:
    showHospitalStructureNav();
        break;
    case 9:
        saveDataToFile();
        break;
    case 10:
        loadDataFromFile();
        break;
    case 11:
        return 0;
        break;
    default:
        printf("Invalid option! Please try again.\n");
        homePage();  
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
        printf("Invalid option! Please try again.\n");
        managePatients();  
        break;
    }

 }
void addPatientNav() {
    char name[30];
    int age;
    char medicalCase[200];
    char address[150];
    condition patientCondition;
    department patientDepartment;
    int conditionChoice, departmentChoice;
    
    printf("\n--- Add Patient ---\n");
    while (getchar() != '\n');
    
    printf("1-Enter the patient name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline character
    
    printf("2-Enter the patient age: ");
    scanf("%d", &age);
    while (getchar() != '\n'); // Clear input buffer after scanf
    
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
    
    // Convert the choice to the condition enum
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
        default:
            patientCondition = normal; // Default
            printf("Invalid choice, setting to Normal.\n");
    }
    
    while (getchar() != '\n'); // Clear input buffer
    
    printf("6-Select patient department:\n");
    printf("   1. Lab\n");
    printf("   2. Cardiology\n");
    printf("   3. Physiology\n");
    printf("   4. Emergency\n");
    printf("Enter choice (1-4): ");
    scanf("%d", &departmentChoice);
    
    // Convert the choice to the department enum
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
            patientDepartment = emergency;
            break;
        default:
            patientDepartment = emergency; // Default
            printf("Invalid choice, setting to Emergency.\n");
    }
    
    // Now call the addPatient function with the collected data
    addPatient(name, age, medicalCase, address, patientCondition, patientDepartment);
    
}
void editPatientNav() {
    int patientID;
    int editChoice;
    char name[30];
    int age;
    char medicalCase[200];
    char address[150];
    condition patientCondition;
    department patientDepartment;
    int conditionChoice, departmentChoice;
    
    printf("Enter the Patient ID to edit: ");
    scanf("%d", &patientID);
    while (getchar() != '\n'); // Clear input buffer
    
    // Assume you have a function to check if the patient exists
    // If the patient doesn't exist, return
    if (!patientExists(patientID)) {
        printf("Patient with ID %d does not exist.\n", patientID);
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
            updatePatientName(patientID, name);
            break;
            
        case 2: // Edit Age
            printf("Enter new age: ");
            scanf("%d", &age);
            while (getchar() != '\n');
            updatePatientAge(patientID, age);
            break;
            
        case 3: // Edit Medical Case
            printf("Enter new medical case: ");
            fgets(medicalCase, sizeof(medicalCase), stdin);
            medicalCase[strcspn(medicalCase, "\n")] = 0;
            updatePatientMedicalCase(patientID, medicalCase);
            break;
            
        case 4: // Edit Address
            printf("Enter new address: ");
            fgets(address, sizeof(address), stdin);
            address[strcspn(address, "\n")] = 0;
            updatePatientAddress(patientID, address);
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
            
            switch(conditionChoice) {
                case 1: patientCondition = urgence; break;
                case 2: patientCondition = danger; break;
                case 3: patientCondition = normal; break;
                case 4: patientCondition = visit; break;
                default:
                    patientCondition = normal; 
                    printf("Invalid choice, setting to Normal.\n");
            }
            updatePatientCondition(patientID, patientCondition);
            break;
            
        case 6: // Edit Department
            printf("Select new patient department:\n");
            printf("   1. Lab\n");
            printf("   2. Cardiology\n");
            printf("   3. Physiology\n");
            printf("   4. Emergency\n");
            printf("Enter choice (1-4): ");
            scanf("%d", &departmentChoice);
            while (getchar() != '\n');
            
            switch(departmentChoice) {
                case 1: patientDepartment = lab; break;
                case 2: patientDepartment = cardiology; break;
                case 3: patientDepartment = physiology; break;
                case 4: patientDepartment = emergency; break;
                default:
                    patientDepartment = emergency;
                    printf("Invalid choice, setting to Emergency.\n");
            }
            updatePatientDepartment(patientID, patientDepartment);
            break;
            
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
            
            switch(conditionChoice) {
                case 1: patientCondition = urgence; break;
                case 2: patientCondition = danger; break;
                case 3: patientCondition = normal; break;
                case 4: patientCondition = visit; break;
                default:
                    patientCondition = normal;
                    printf("Invalid choice, setting to Normal.\n");
            }
            
            printf("Select new patient department:\n");
            printf("   1. Lab\n");
            printf("   2. Cardiology\n");
            printf("   3. Physiology\n");
            printf("   4. Emergency\n");
            printf("Enter choice (1-4): ");
            scanf("%d", &departmentChoice);
            while (getchar() != '\n');
            
            switch(departmentChoice) {
                case 1: patientDepartment = lab; break;
                case 2: patientDepartment = cardiology; break;
                case 3: patientDepartment = physiology; break;
                case 4: patientDepartment = emergency; break;
                default:
                    patientDepartment = emergency;
                    printf("Invalid choice, setting to Emergency.\n");
            }
            
            // Update all patient information at once
            updatePatient(patientID, name, age, medicalCase, address, patientCondition, patientDepartment);
            break;
            
        default:
            printf("Invalid choice.\n");
            editPatientNav();
            return;
    }
    
    printf("Patient information updated successfully!\n");
}

void viewPatientNav(){
    printf("enter id of patient you want to view");
    char id[14];
    fgets(id,sizeof(id),stdin);
    //find patient
    Patient patient = findPatientById(id);
    if (patient.id == NULL) {
        printf("No patient found with ID: %s\n", id);
        return;
    }
    printf("\n--- Patient Details ---\n");
    printf("Name: %s\n", patient.name);
    printf("Age: %d\n", patient.age);
    printf("Medical Case: %s\n", patient.medicalCase);
    printf("Address: %s\n", patient.address);
    printf("Condition: %s\n", conditionToString(patient.condition)); // Convert enum to string
    printf("Department: %s\n", departmentToString(patient.department)); // Convert enum to string
    printf("-----------------------\n");

};
void addPatientToQueue(){
    printf("enter id of patient you want to add to queue");
    char id[14];
    fgets(id,sizeof(id),stdin);
    //find patient
    Patient patient = findPatientById(id);
    if (patient.id == NULL) {
        printf("No patient found with ID: %s\n", id);
        return;
    }
    //add to queue
    addToQueue(patient);
};
void dischargePatient(){
    printf("enter id of patient you want to discharge");
    char id[14];
    fgets(id,sizeof(id),stdin);
    //find patient
    Patient patient = findPatientById(id);
    if (patient.id == NULL) {
        printf("No patient found with ID: %s\n", id);
        return;
    }
    //discharge patient
    discharge(patient);
};
void undoLastDischarge(){

};
