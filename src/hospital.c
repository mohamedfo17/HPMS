#include "../headers/departments.h"
#include  "../headers/hospital.h"
#include <stdio.h>

// Assuming departments is defined as an external variable in another file
extern departmentInfo departments[4];

void showHospitalStructureNav(){
    printf("Hospital Structure:\n");
    printf("1. Departments\n");
    printf("2. Balance\n");
    printf("3. Surgery Rooms\n");
    printf("4. Pharmacy\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            showDepa();
            break;
    /*    case 2:
            showBalence();
            break;*/
        case 3:
            showSurgeryRooms();
            break;
       
        default:
            printf("Invalid choice!\n");
            break;
    }
};

void showDepa(){
    printf("Departments:\n");
    for (int i = 0; i < 4; i++)
    {
        printf("Department of %s\n",departmentToString(departments[i].department));
        printf("Number of doctors is %d\n",departments[i].numDoc);
        printf("Number of patients is %d\n",departments[i].numPat);
        printf("Surgery rooms is %d\n",departments[i].surgeryRoomsDepa.total);
        printf("Patient rooms is %d\n",departments[i].patientRoomsDepa.total);


        printf("Balance is %.2f $\n",departments[i].balence);
        printf("--------------------------------------------------\n");
    
    }
    
};

/*void showBalence(){
    printf("The hospital balence is %d\n",departments[0].balence+departments[1].balence+departments[2].balence+departments[3].balence+pharmaBudget);
};*/
void showSurgeryRooms(){
    printf("the number of surgery rooms in the hospital is %d\n",departments[0].surgeryRoomsDepa.total+departments[1].surgeryRoomsDepa.total+departments[2].surgeryRoomsDepa.total+departments[3].surgeryRoomsDepa.total);
    printf("free surgery rooms are %d\n",departments[0].surgeryRoomsDepa.empty + departments[1].surgeryRoomsDepa.empty + departments[2].surgeryRoomsDepa.empty + departments[3].surgeryRoomsDepa.empty );//complete it
    printf("busy surgery rooms are %d\n",departments[0].surgeryRoomsDepa.busy + departments[1].surgeryRoomsDepa.busy + departments[2].surgeryRoomsDepa.busy + departments[3].surgeryRoomsDepa.busy );//complete it
    printf("the number of patient (scan and visit rooms) rooms in the hospital is %d\n",departments[0].patientRoomsDepa.total+departments[1].patientRoomsDepa.total+departments[2].patientRoomsDepa.total+departments[3].patientRoomsDepa.total);
    printf("free patient rooms are %d\n",departments[0].patientRoomsDepa.empty + departments[1].patientRoomsDepa.empty + departments[2].patientRoomsDepa.empty + departments[3].patientRoomsDepa.empty );//complete it
    printf("busy patient rooms are %d\n",departments[0].patientRoomsDepa.busy + departments[1].patientRoomsDepa.busy + departments[2].patientRoomsDepa.busy + departments[3].patientRoomsDepa.busy);//complete it

};
