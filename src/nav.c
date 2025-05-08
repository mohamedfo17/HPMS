#include "../headers/nav.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../headers/patients.h"
#include "../headers/doctors.h"
#include "../headers/hospital.h"


 

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
            updatePatientDepartment(patient, patientDepartment);
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
    scanf("%d", &deleteCondition);
    department deleteDepartment;
    scanf("%d", &deleteDepartment);
    deletePat(id,deleteCondition,deleteDepartment);
};
void viewPatientNav(){
    printf("enter id of patient you want to view\n and his condition \n ");
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
    printf("\n--- Patient Details ---\n");
    printf("Name: %s\n", patient->name);
    printf("Age: %d\n", patient->age);
    printf("Medical Case: %s\n", patient->medicalCase);
    printf("Address: %s\n", patient->address);
    printf("Condition: %s\n", conditionToString(patient->condition)); // Convert enum to string
    printf("Department: %s\n", departmentToString(patient->department)); // Ensure departmentToString is defined and returns a valid string
    // Ensure departmentToString is defined and returns a valid string
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
    while (getchar() != '\n'); // Clear input buffer

    printf("1-Enter the doctor name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("2-Enter the doctor age: ");
    scanf("%d", &age);
    while (getchar() != '\n'); // Clear input buffer after scanf

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
    printf("6-Select patient department:\n");
    printf("   1. Lab\n");
    printf("   2. Cardiology\n");
    printf("   3. Physiology\n");
    printf("   4. Emergency\n");
    printf("Enter choice (1-4): ");
    scanf("%d", &departmentDoc);
    // Convert the choice to the rank enum
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
            doctorRank = intern; // Default
            printf("Invalid choice, setting to Intern.\n");
    }
    addDoctor(name, age, specialty, address, doctorRank,departmentDoc);}
    else{
        printf("there is no available position for this doctor\n");
    }
    //try no switch here
    // Call your addDoctor function here (you should have one implemented)
   
}
//edit doctors nav is requiered;
void deleteDoctorNav() {
    printf("Enter the ID of the doctor you want to delete,\nfollowed by their rank:\n and department \n");

    char id[15];
    int ch;
while ((ch = getchar()) != '\n' && ch != EOF); // flush stdin

    fgets(id, sizeof(id), stdin);
    
    // Remove newline if present
    size_t len = strlen(id);
    if (len > 0 && id[len - 1] == '\n') {
        id[len - 1] = '\0';}

    rank deleteRank;
    scanf("%d", &deleteRank);
    department deleteDepartment;
    scanf("%d", &deleteDepartment);
    deleteDoc(id,deleteDepartment, deleteRank);
}
void viewDoctorNav() {
    printf("Enter the ID of the doctor you want to view\n");

    char id[15];
    int ch;
while ((ch = getchar()) != '\n' && ch != EOF); // flush stdin

    fgets(id, sizeof(id), stdin);
    
    // Remove newline if present
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
    printf("Rank: %s\n", rankToString(doc->rank)); // Convert rank enum to string
    printf("Department: %s\n", departmentToString(doc->department)); // Convert department enum to string
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
            printf("   4. Emergency\n");
            printf("Enter choice (1-4): ");
            scanf("%d", &departmentChoice);
            while (getchar() != '\n');
            if( checkPositionAvailibility( doctor->rank, departmentChoice)){
            switch (departmentChoice) {
                case 1: doctorDepartment = lab; break;
                case 2: doctorDepartment = cardiology; break;
                case 3: doctorDepartment = physiology; break;
                case 4: doctorDepartment = emergency; break;
                default:
                    doctorDepartment = emergency;
                    printf("Invalid choice, setting to Emergency.\n");
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
            printf("   4. Emergency\n");
            printf("Enter choice (1-4): ");
            scanf("%d", &departmentChoice);
            while (getchar() != '\n');
        
            switch (departmentChoice) {
                case 1: doctorDepartment = lab; break;
                case 2: doctorDepartment = cardiology; break;
                case 3: doctorDepartment = physiology; break;
                case 4: doctorDepartment = emergency; break;
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


/*void addPatientToQueue(){
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
};*/
/*void dischargePatient(){
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

};*/
void manageDoctors() {
    printf("\n--- Doctor Management ---\n");
    printf("1. Add Doctor\n");
    printf("2. Edit Doctor\n");
    printf("3. View Doctor\n");
    printf("4. Delete Doctor\n");
    printf("5. View All Doctors\n");
    printf("6. Back\n");
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
        homePage();  // Return to main menu
        break;
    default:
        printf("Invalid option! Please try again.\n");
        manageDoctors();  
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
 void homePage() {
    while (1)
    {
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
   /* case 3:
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
        break;*/
    case 8:
    showHospitalStructureNav();
        break;
   /* case 9:
        saveDataToFile();
        break;
    case 10:
        loadDataFromFile();
        break;*/
    case 11:
        exit(0);
        break;
    default:
        printf("Invalid option! Please try again.\n");
        homePage();  
        break;
    }}
}