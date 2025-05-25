// persistence.c - Hospital Management System Data Persistence
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/patients.h"
#include "../headers/doctors.h"
#include "../headers/departments.h"
#include "../headers/queue.h"
#include "../headers/stack.h"
#include "../headers/treeDoc.h"
#include "../headers/treePat.h"

#define SAVE_FILE "hospital_data.dat"
#define BACKUP_FILE "hpms_backup.hpms"

// External variables from your modules
extern int employeNum;
extern int patientNum;
extern doctor* doctors[200];
extern patient* patients[200];
extern departmentInfo departments[4];
extern TreeNode *rootEmeDoc, *rootCarDoc, *rootPhyDoc;
extern TreeNodePat *rootEmePat, *rootCarPat, *rootPhyPat;
extern stack* top; // Assuming you have this

// Helper structure for saving queue data
typedef struct {
    char patientId[15];
    char patientName[30];
    int age;
    char medicalCase[200];
    char address[150];
    condition patientCondition;
    department patientDepartment;
    bool isAssured;
    int sessionCost;
} QueuePatientData;

// Forward declarations
int saveCounters(FILE* file);
int saveArrays(FILE* file);
int saveLinkedStructures(FILE* file);
int loadCounters(FILE* file);
int loadArrays(FILE* file);
int loadLinkedStructures(FILE* file);
void saveTreePreOrder(TreeNode* root, FILE* file, int* nodeCount);
void saveTreePatPreOrder(TreeNodePat* root, FILE* file, int* nodeCount);
TreeNode* loadTreePreOrder(FILE* file, int* nodeCount);
TreeNodePat* loadTreePatPreOrder(FILE* file, int* nodeCount);

// ==================== MAIN SAVE/LOAD FUNCTIONS ====================

int saveAllData(void) {
    FILE* file = fopen(SAVE_FILE, "wb");
    if (file == NULL) {
        printf("Error: Cannot create save file '%s'!\n", SAVE_FILE);
        return 0;
    }

    printf("Saving hospital data...\n");

    // Save in fixed order
    if (!saveCounters(file)) {
        printf("Error saving counters!\n");
        fclose(file);
        return 0;
    }

    if (!saveArrays(file)) {
        printf("Error saving arrays!\n");
        fclose(file);
        return 0;
    }

    if (!saveLinkedStructures(file)) {
        printf("Error saving linked structures!\n");
        fclose(file);
        return 0;
    }

    fclose(file);
    printf("✓ Data saved successfully to '%s'\n", SAVE_FILE);
    
    // Create backup
    FILE* backup = fopen(BACKUP_FILE, "wb");
    if (backup != NULL) {
        FILE* source = fopen(SAVE_FILE, "rb");
        if (source != NULL) {
            char buffer[1024];
            size_t bytes;
            while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
                fwrite(buffer, 1, bytes, backup);
            }
            fclose(source);
            printf("✓ Backup created: '%s'\n", BACKUP_FILE);
        }
        fclose(backup);
    }

    return 1;
}

int loadAllData(void) {
    FILE* file = fopen(SAVE_FILE, "rb");
    if (file == NULL) {
        printf("Save file '%s' not found. Starting with empty data.\n", SAVE_FILE);
        return 0;
    }

    printf("Loading hospital data...\n");

    // Load in same order as saved
    if (!loadCounters(file)) {
        printf("Error loading counters!\n");
        fclose(file);
        return 0;
    }

    if (!loadArrays(file)) {
        printf("Error loading arrays!\n");
        fclose(file);
        return 0;
    }

    if (!loadLinkedStructures(file)) {
        printf("Error loading linked structures!\n");
        fclose(file);
        return 0;
    }

    fclose(file);
    printf("✓ Data loaded successfully from '%s'\n", SAVE_FILE);
    printf("  - Doctors loaded: %d\n", employeNum);
    printf("  - Patients loaded: %d\n", patientNum);
    
    return 1;
}

// ==================== SAVE FUNCTIONS ====================

int saveCounters(FILE* file) {
    // Save all counter variables
    if (fwrite(&employeNum, sizeof(int), 1, file) != 1) return 0;
    if (fwrite(&patientNum, sizeof(int), 1, file) != 1) return 0;
    
    // Save department counts
    for (int i = 0; i < 4; i++) {
        if (fwrite(&departments[i].numDoc, sizeof(int), 1, file) != 1) return 0;
        if (fwrite(&departments[i].numPat, sizeof(int), 1, file) != 1) return 0;
    }
    
    return 1;
}

int saveArrays(FILE* file) {
    // Save doctor array data (not pointers!)
    for (int i = 0; i < employeNum; i++) {
        if (doctors[i] != NULL) {
            // Save doctor data
            if (fwrite(doctors[i], sizeof(doctor), 1, file) != 1) return 0;
        }
    }

    // Save patient array data
    for (int i = 0; i < patientNum; i++) {
        if (patients[i] != NULL) {
            // Save patient data (without assignedDoc pointer)
            patient tempPatient = *patients[i];
            tempPatient.assignedDoc = NULL; // Don't save pointer
            if (fwrite(&tempPatient, sizeof(patient), 1, file) != 1) return 0;
            
            // Save assigned doctor ID separately
            if (patients[i]->assignedDoc != NULL) {
                if (fwrite(patients[i]->assignedDoc->id, sizeof(char), 15, file) != 15) return 0;
            } else {
                char emptyId[15] = {0};
                if (fwrite(emptyId, sizeof(char), 15, file) != 15) return 0;
            }
        }
    }

    // Save department data
    for (int i = 0; i < 4; i++) {
        departmentInfo tempDept = departments[i];
        // Clear pointers before saving
        memset(tempDept.doctors, 0, sizeof(tempDept.doctors));
        memset(tempDept.patients, 0, sizeof(tempDept.patients));
        
        if (fwrite(&tempDept, sizeof(departmentInfo), 1, file) != 1) return 0;
    }

    return 1;
}

int saveLinkedStructures(FILE* file) {
    int treeNodeCount;
    long countPos, endPos;
    int placeholder = 0;

    // ---- Emergency Doctor Tree ----
    treeNodeCount = 0;
    countPos = ftell(file);
    if (fwrite(&placeholder, sizeof(int), 1, file) != 1) return 0;
    saveTreePreOrder(rootEmeDoc, file, &treeNodeCount);
    endPos = ftell(file);
    fseek(file, countPos, SEEK_SET);
    if (fwrite(&treeNodeCount, sizeof(int), 1, file) != 1) return 0;
    fseek(file, endPos, SEEK_SET);

    // ---- Cardiology Doctor Tree ----
    treeNodeCount = 0;
    countPos = ftell(file);
    if (fwrite(&placeholder, sizeof(int), 1, file) != 1) return 0;
    saveTreePreOrder(rootCarDoc, file, &treeNodeCount);
    endPos = ftell(file);
    fseek(file, countPos, SEEK_SET);
    if (fwrite(&treeNodeCount, sizeof(int), 1, file) != 1) return 0;
    fseek(file, endPos, SEEK_SET);

    // ---- Physiology Doctor Tree ----
    treeNodeCount = 0;
    countPos = ftell(file);
    if (fwrite(&placeholder, sizeof(int), 1, file) != 1) return 0;
    saveTreePreOrder(rootPhyDoc, file, &treeNodeCount);
    endPos = ftell(file);
    fseek(file, countPos, SEEK_SET);
    if (fwrite(&treeNodeCount, sizeof(int), 1, file) != 1) return 0;
    fseek(file, endPos, SEEK_SET);

    // ---- Emergency Patient Tree ----
    treeNodeCount = 0;
    countPos = ftell(file);
    if (fwrite(&placeholder, sizeof(int), 1, file) != 1) return 0;
    saveTreePatPreOrder(rootEmePat, file, &treeNodeCount);
    endPos = ftell(file);
    fseek(file, countPos, SEEK_SET);
    if (fwrite(&treeNodeCount, sizeof(int), 1, file) != 1) return 0;
    fseek(file, endPos, SEEK_SET);

    // ---- Cardiology Patient Tree ----
    treeNodeCount = 0;
    countPos = ftell(file);
    if (fwrite(&placeholder, sizeof(int), 1, file) != 1) return 0;
    saveTreePatPreOrder(rootCarPat, file, &treeNodeCount);
    endPos = ftell(file);
    fseek(file, countPos, SEEK_SET);
    if (fwrite(&treeNodeCount, sizeof(int), 1, file) != 1) return 0;
    fseek(file, endPos, SEEK_SET);

    // ---- Physiology Patient Tree ----
    treeNodeCount = 0;
    countPos = ftell(file);
    if (fwrite(&placeholder, sizeof(int), 1, file) != 1) return 0;
    saveTreePatPreOrder(rootPhyPat, file, &treeNodeCount);
    endPos = ftell(file);
    fseek(file, countPos, SEEK_SET);
    if (fwrite(&treeNodeCount, sizeof(int), 1, file) != 1) return 0;
    fseek(file, endPos, SEEK_SET);

    // ---- Doctor Queues ----
    for (int i = 0; i < employeNum; i++) {
        if (doctors[i] != NULL && doctors[i]->doctorQueue != NULL) {
            Queue* q = doctors[i]->doctorQueue;

            // Count queue size
            int queueSize = 0;
            node* current = q->front;
            while (current != NULL) {
                queueSize++;
                current = current->next;
            }

            // Write queue size
            if (fwrite(&queueSize, sizeof(int), 1, file) != 1) {
                perror("Error writing queue size");
                return 0;
            }

            // Write queue data
            current = q->front;
            while (current != NULL) {
                QueuePatientData qData;
                strcpy(qData.patientId, current->patient->id);
                strcpy(qData.patientName, current->patient->name);
                qData.age = current->patient->age;
                strcpy(qData.medicalCase, current->patient->medicalCase);
                strcpy(qData.address, current->patient->address);
                qData.patientCondition = current->patient->condition;
                qData.patientDepartment = current->patient->department;
                qData.isAssured = current->patient->isAssured;
                qData.sessionCost = current->patient->sessionCost;

                if (fwrite(&qData, sizeof(QueuePatientData), 1, file) != 1) {
                    perror("Error writing queue data");
                    return 0;
                }

                current = current->next;
            }

        } else {
            // No queue, write 0
            int queueSize = 0;
            if (fwrite(&queueSize, sizeof(int), 1, file) != 1) {
                perror("Error writing empty queue size");
                return 0;
            }
        }
    }

    return 1;
}


// ==================== LOAD FUNCTIONS ====================

int loadCounters(FILE* file) {
    // Load counter variables
    if (fread(&employeNum, sizeof(int), 1, file) != 1) return 0;
    if (fread(&patientNum, sizeof(int), 1, file) != 1) return 0;
    
    // Load department counts
    for (int i = 0; i < 4; i++) {
        if (fread(&departments[i].numDoc, sizeof(int), 1, file) != 1) return 0;
        if (fread(&departments[i].numPat, sizeof(int), 1, file) != 1) return 0;
    }
    
    return 1;
}

int loadArrays(FILE* file) {
    // Load and recreate doctor array
    for (int i = 0; i < employeNum; i++) {
        doctors[i] = (doctor*)malloc(sizeof(doctor));
        if (doctors[i] == NULL) {
            printf("Memory allocation failed for doctor %d\n", i);
            return 0;
        }
        
        if (fread(doctors[i], sizeof(doctor), 1, file) != 1) {
            free(doctors[i]);
            return 0;
        }
        
        // Initialize queue pointer (will be rebuilt later)
        doctors[i]->doctorQueue = NULL;
    }

    // Load and recreate patient array
    for (int i = 0; i < patientNum; i++) {
        patients[i] = (patient*)malloc(sizeof(patient));
        if (patients[i] == NULL) {
            printf("Memory allocation failed for patient %d\n", i);
            return 0;
        }
        
        if (fread(patients[i], sizeof(patient), 1, file) != 1) {
            free(patients[i]);
            return 0;
        }
        
        // Load assigned doctor ID
        char doctorId[15];
        if (fread(doctorId, sizeof(char), 15, file) != 15) return 0;
        
        // Find and assign doctor pointer
        patients[i]->assignedDoc = NULL;
        if (strlen(doctorId) > 0) {
            for (int j = 0; j < employeNum; j++) {
                if (strcmp(doctors[j]->id, doctorId) == 0) {
                    patients[i]->assignedDoc = doctors[j];
                    break;
                }
            }
        }
    }

    // Load department data
    for (int i = 0; i < 4; i++) {
        departmentInfo tempDept;
        if (fread(&tempDept, sizeof(departmentInfo), 1, file) != 1) return 0;
        
        // Copy non-pointer data
        departments[i].department = tempDept.department;
        departments[i].numDoc = tempDept.numDoc;
        departments[i].numPat = tempDept.numPat;
        departments[i].surgeryRoomsDepa = tempDept.surgeryRoomsDepa;
        departments[i].patientRoomsDepa = tempDept.patientRoomsDepa;
        departments[i].income = tempDept.income;
        departments[i].expenses = tempDept.expenses;
        departments[i].balence = tempDept.balence;
        
        // Rebuild doctor and patient pointers
        int docIndex = 0, patIndex = 0;
        for (int j = 0; j < employeNum && docIndex < departments[i].numDoc; j++) {
            if (doctors[j]->department == i + 1) {
                departments[i].doctors[docIndex++] = doctors[j];
            }
        }
        
        for (int j = 0; j < patientNum && patIndex < departments[i].numPat; j++) {
            if (patients[j]->department == i + 1) {
                departments[i].patients[patIndex++] = patients[j];
            }
        }
    }

    return 1;
}

int loadLinkedStructures(FILE* file) {
    // Load Trees (simplified - would need full tree reconstruction logic)
    // For now, trees will be rebuilt by re-inserting loaded doctors/patients
    
    // Rebuild doctor trees
    rootEmeDoc = rootCarDoc = rootPhyDoc = NULL;
    for (int i = 0; i < employeNum; i++) {
        if (doctors[i]->department == 0) {
            // Insert into emergency tree (simplified)
        } else if (doctors[i]->department == 1) {
            // Insert into cardiology tree
        } else if (doctors[i]->department == 2) {
            // Insert into physiology tree
        }
    }
    
    // Rebuild patient trees similarly
    rootEmePat = rootCarPat = rootPhyPat = NULL;
    
    // Load and rebuild doctor queues
    for (int i = 0; i < employeNum; i++) {
        int queueSize;
        if (fread(&queueSize, sizeof(int), 1, file) != 1) return 0;
        
        if (queueSize > 0) {
            doctors[i]->doctorQueue = (Queue*)malloc(sizeof(Queue));
            createQueue(doctors[i]->doctorQueue);
            
            for (int j = 0; j < queueSize; j++) {
                QueuePatientData qData;
                if (fread(&qData, sizeof(QueuePatientData), 1, file) != 1) return 0;
                
                // Find patient by ID and add to queue
                for (int k = 0; k < patientNum; k++) {
                    if (strcmp(patients[k]->id, qData.patientId) == 0) {
                        enqueue(doctors[i]->doctorQueue, patients[k], doctors[i]);
                        break;
                    }
                }
            }
        }
    }

    return 1;
}

// ==================== TREE SAVE/LOAD HELPERS ====================

void saveTreePreOrder(TreeNode* root, FILE* file, int* nodeCount) {
    if (root == NULL) {
        int marker = -1;
        fwrite(&marker, sizeof(int), 1, file);
        return;
    }
    
    // Save doctor data
    fwrite(root->doctor, sizeof(doctor), 1, file);
    (*nodeCount)++;
    
    // Recursively save children
    saveTreePreOrder(root->left, file, nodeCount);
    saveTreePreOrder(root->right, file, nodeCount);
}

void saveTreePatPreOrder(TreeNodePat* root, FILE* file, int* nodeCount) {
    if (root == NULL) {
        int marker = -1;
        fwrite(&marker, sizeof(int), 1, file);
        return;
    }
    
    // Save patient data (without assignedDoc pointer)
    patient tempPatient = *root->patient;
    tempPatient.assignedDoc = NULL;
    fwrite(&tempPatient, sizeof(patient), 1, file);
    (*nodeCount)++;
    
    // Recursively save children
    saveTreePatPreOrder(root->left, file, nodeCount);
    saveTreePatPreOrder(root->right, file, nodeCount);
}

// ==================== MENU INTEGRATION ====================

void displayPersistenceMenu(void) {
    printf("\n=== Data Management ===\n");
    printf("1. Save All Data\n");
    printf("2. Load All Data\n");
    printf("3. Create Backup\n");
    printf("4. Load from Backup\n");
    printf("5. Auto-Save Settings\n");
    printf("0. Return to Main Menu\n");
    printf("Choice: ");
}

void handlePersistenceMenu(void) {
    int choice;
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            if (saveAllData()) {
                printf("✓ All hospital data saved successfully!\n");
            } else {
                printf("✗ Failed to save data!\n");
            }
            break;
            
        case 2:
            if (loadAllData()) {
                printf("✓ All hospital data loaded successfully!\n");
            } else {
                printf("✗ Failed to load data!\n");
            }
            break;
            
        case 3: {
            FILE* source = fopen(SAVE_FILE, "rb");
            FILE* backup = fopen(BACKUP_FILE, "wb");
            if (source && backup) {
                char buffer[1024];
                size_t bytes;
                while ((bytes = fread(buffer, 1, sizeof(buffer), source)) > 0) {
                    fwrite(buffer, 1, bytes, backup);
                }
                printf("✓ Backup created successfully!\n");
            } else {
                printf("✗ Failed to create backup!\n");
            }
            if (source) fclose(source);
            if (backup) fclose(backup);
            break;
        }
        
        case 4: {
            FILE* backup = fopen(BACKUP_FILE, "rb");
            FILE* main = fopen(SAVE_FILE, "wb");
            if (backup && main) {
                char buffer[1024];  
                size_t bytes;
                while ((bytes = fread(buffer, 1, sizeof(buffer), backup)) > 0) {
                    fwrite(buffer, 1, bytes, main);
                }
                fclose(backup);
                fclose(main);
                if (loadAllData()) {
                    printf("✓ Data restored from backup!\n");
                }
            } else {
                printf("✗ Failed to restore from backup!\n");
            }
            break;
        }
        
        case 5:
            printf("Auto-save feature not implemented yet.\n");
            break;
            
        case 0:
            return;
            
        default:
            printf("Invalid choice!\n");
    }
}

// ==================== UTILITY FUNCTIONS ====================

int validateSaveFile(void) {
    FILE* file = fopen(SAVE_FILE, "rb");
    if (file == NULL) return 0;
    
    // Basic validation - check if counters are reasonable
    int empCount, patCount;
    if (fread(&empCount, sizeof(int), 1, file) != 1 || 
        fread(&patCount, sizeof(int), 1, file) != 1) {
        fclose(file);
        return 0;
    }
    
    fclose(file);
    
    // Check if counts are within reasonable bounds
    return (empCount >= 0 && empCount <= 200 && 
            patCount >= 0 && patCount <= 200);
}

void printDataSummary(void) {
    printf("\n=== Hospital Data Summary ===\n");
    printf("Total Doctors: %d\n", employeNum);
    printf("Total Patients: %d\n", patientNum);
    
    for (int i = 0; i < 4; i++) {
        printf("Department %s:\n", departmentToString(i + 1));
        printf("  - Doctors: %d\n", departments[i].numDoc);
        printf("  - Patients: %d\n", departments[i].numPat);
        printf("  - Balance: %d\n", departments[i].balence);
    }
}