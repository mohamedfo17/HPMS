#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <stdio.h>
#include <stdbool.h>
#include "treePat.h"   // for TreeNode
#include "treeDoc.h"  // for TreeNodePat


int saveAllData(void);


int loadAllData(void);

int saveCounters(FILE* file);


int saveArrays(FILE* file);


int saveLinkedStructures(FILE* file);


int loadCounters(FILE* file);


int loadArrays(FILE* file);


int loadLinkedStructures(FILE* file);






void saveTreePreOrder( TreeNode* root, FILE* file, int* nodeCount);


void saveTreePatPreOrder(TreeNodePat* root, FILE* file, int* nodeCount);

 TreeNode* loadTreePreOrder(FILE* file, int* nodeCount);

 TreeNodePat* loadTreePatPreOrder(FILE* file, int* nodeCount);


void displayPersistenceMenu(void);

void handlePersistenceMenu(void);


int validateSaveFile(void);


void printDataSummary(void);

int createBackup(void);

int restoreFromBackup(void);

void enableAutoSave(int intervalMinutes);

void disableAutoSave(void);

void checkAutoSave(void);

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

 
typedef struct {
    char patientId[15];
    char patientName[30];
    int age;
    char medicalCase[200];
    char address[150];
    condition patientCondition;
    department patientDepartment;
    bool isAssured;
    char assignedDoctorId[15];
} StackPatientData;


#define SAVE_FILE "hospital_data.dat"
#define BACKUP_FILE "hpms_backup.hpms"
#define TEMP_FILE "hospital_temp.tmp"

#define HOSPITAL_FILE_MAGIC 0x48534D50  // "HSMP" in hex

#define FILE_FORMAT_VERSION 1


#define SAVE_SUCCESS 1
#define SAVE_FAILED 0
#define LOAD_SUCCESS 1
#define LOAD_FAILED 0
#define FILE_NOT_FOUND -1
#define FILE_CORRUPTED -2
#define MEMORY_ERROR -3

#endif // PERSISTENCE_H