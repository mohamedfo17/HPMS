#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/patients.h"
#include "../headers/doctors.h"
#include "../headers/departments.h"
#include "../headers/treeDoc.h"
#include "../headers/treePat.h"

#define SAVE_FILE "hospital_data.dat"

extern int employeNum;
extern int patientNum;
extern doctor* doctors[200];
extern patient* patients[200];
extern departmentInfo departments[4];

extern int *flipP;
extern int *firstSearchP;
extern int *flip;
extern int *firstSearch;

extern TreeNode *rootEmeDoc;
extern TreeNode *rootCarDoc;
extern TreeNode *rootPhyDoc;
extern TreeNodePat *rootEmePat;
extern TreeNodePat *rootCarPat;
extern TreeNodePat *rootPhyPat;

int saveAllData(void);
int loadAllData(void);
int saveData(FILE *file);
int loadData(FILE *file);
void cleanup(void);
void rebuildTrees(void);

// ===================== SAVE ======================

int saveAllData(void) {
    FILE *file = fopen(SAVE_FILE, "wb");
    if (!file) {
        printf("Error: Cannot open file for saving.\n");
        return 0;
    }

    if (!saveData(file)) {
        printf("Error saving data.\n");
        fclose(file);
        return 0;
    }

    fclose(file);
    printf("✓ Data saved successfully.\n");
    return 1;
}

int saveData(FILE *file) {
    // Save counts
    if (fwrite(&employeNum, sizeof(int), 1, file) != 1) return 0;
    if (fwrite(&patientNum, sizeof(int), 1, file) != 1) return 0;

    // Save doctors
    for (int i = 0; i < employeNum; i++) {
        if (fwrite(doctors[i], sizeof(doctor), 1, file) != 1) return 0;
    }

    // Save patients
    for (int i = 0; i < patientNum; i++) {
        patient temp = *patients[i];
        temp.assignedDoc = NULL;  // avoid pointer serialization
        if (fwrite(&temp, sizeof(patient), 1, file) != 1) return 0;
    }

    return 1;
}

// ===================== LOAD ======================

int loadAllData(void) {
    FILE *file = fopen(SAVE_FILE, "rb");
    if (!file) {
        printf("No save file found. Starting fresh.\n");
        return 0;
    }

    cleanup();

    if (!loadData(file)) {
        printf("Error loading data.\n");
        fclose(file);
        return 0;
    }

    fclose(file);
    rebuildTrees();
    printf("✓ Data loaded successfully.\n");
    return 1;
}

int loadData(FILE *file) {
    if (fread(&employeNum, sizeof(int), 1, file) != 1) return 0;
    if (fread(&patientNum, sizeof(int), 1, file) != 1) return 0;

    doctor tempDoctors[200];
    patient tempPatients[200];
    int docCount = employeNum;
    int patCount = patientNum;
    employeNum = 0;
    patientNum = 0;

    for (int i = 0; i < docCount; i++) {
        if (fread(&tempDoctors[i], sizeof(doctor), 1, file) != 1) return 0;
    }

    for (int i = 0; i < patCount; i++) {
        if (fread(&tempPatients[i], sizeof(patient), 1, file) != 1) return 0;
    }

    for (int i = 0; i < docCount; i++) {
        addDoctor(tempDoctors[i].name, tempDoctors[i].age, tempDoctors[i].speciality,
                  tempDoctors[i].address, tempDoctors[i].rank, tempDoctors[i].department);
        strncpy(doctors[i]->id, tempDoctors[i].id, 14);
    }

    for (int i = 0; i < patCount; i++) {
        addPatient(tempPatients[i].name, tempPatients[i].age, tempPatients[i].medicalCase,
                   tempPatients[i].address, tempPatients[i].condition, tempPatients[i].department,
                   tempPatients[i].isAssured);
        strncpy(patients[i]->id, tempPatients[i].id, 14);
        patients[i]->sessionCost = tempPatients[i].sessionCost;
    }

    return 1;
}

// ===================== CLEANUP + TREE REBUILD ======================

void cleanup(void) {
    for (int i = 0; i < employeNum; i++) {
        if (doctors[i]) {
            free(doctors[i]);
            doctors[i] = NULL;
        }
    }

    for (int i = 0; i < patientNum; i++) {
        if (patients[i]) {
            free(patients[i]);
            patients[i] = NULL;
        }
    }

    for (int i = 0; i < 4; i++) {
        memset(departments[i].doctors, 0, sizeof(departments[i].doctors));
        memset(departments[i].patients, 0, sizeof(departments[i].patients));
        departments[i].numDoc = 0;
        departments[i].numPat = 0;
    }

    rootEmeDoc = rootCarDoc = rootPhyDoc = NULL;
    rootEmePat = rootCarPat = rootPhyPat = NULL;
    employeNum = 0;
    patientNum = 0;
}

void rebuildTrees(void) {
    int n = 0, f = 0, g = 0;
    int *firstInsert = &n;
    int *flip = &f;
    int *firstSearch = &g;

    for (int i = 0; i < employeNum; i++) {
        doctor *d = doctors[i];
        if (d->department == 0)
            rootEmeDoc = insertTree(rootEmeDoc, d, d->id, d->rank, firstInsert, flip);
        else if (d->department == 1)
            rootCarDoc = insertTree(rootCarDoc, d, d->id, d->rank, firstInsert, flip);
        else if (d->department == 2)
            rootPhyDoc = insertTree(rootPhyDoc, d, d->id, d->rank, firstInsert, flip);
        *firstInsert = 1;
    }

    for (int i = 0; i < patientNum; i++) {
        patient *p = patients[i];
        if (p->department == 0)
            rootEmePat = insertTreePat(rootEmePat, p, p->id, p->condition, firstSearchP, flipP);
        else if (p->department == 1)
            rootCarPat = insertTreePat(rootCarPat, p, p->id, p->condition, firstSearchP, flipP);
        else if (p->department == 2)
            rootPhyPat = insertTreePat(rootPhyPat, p, p->id, p->condition, firstSearchP, flipP);
        *firstSearch = 1;
    }

    printf("✓ Trees rebuilt successfully.\n");
}
