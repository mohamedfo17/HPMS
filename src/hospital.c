#include "../headers/departments.h"
#include  "../headers/hospital.h"

/*void showHospitalStructureNav(){
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
        case 2:
            showBalence();
            break;
        case 3:
            showSurgeryRooms();
            break;
        case 4:
            showPharmacy();
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
        printf("Surgery rooms is %d\n",departments[i].surgeryRooms);
        printf("Balance is %d\n",departments[i].balence);

    
    }
    
};

void showBalence(){
    printf("The hospital balence is %d\n",departments[0].balence+departments[1].balence+departments[2].balence+departments[3].balence+pharmaBudget);
};
void showSurgeryRooms(){
    printf("the number of surgery rooms in the hospital is %d",departments[0].surgeryRooms+departments[1].surgeryRooms+departments[2].surgeryRooms+departments[3].surgeryRooms);
    printf("free surgery rooms are %d" );//complete it
    printf("busy surgery rooms are %d" );//complete it

};
void showPharmacy(){};*/