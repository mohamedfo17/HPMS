#include <stdio.h>
#include <string.h>
#include "../headers/nav.h"
#include "../headers/pharmacyMain.h"

#include <stdlib.h>

#define PASSKEY "1234" 
#define MAX_ATTEMPTS 3   

void authenticateUser(void) {
    char input[50];
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS) {
        printf("Enter passkey to access the Hospital Management System: ");
        scanf("%49s", input);

        if (strcmp(input, PASSKEY) == 0) {
            printf("Access granted.\n");
            printf("what system u want to get into \n 1-hospital managment \n 2-pharmacy\n");
            int choice;
            scanf("%d",&choice);
            if (!(choice==1||choice==2))
            {
                printf("wrong ...");
                exit(-1);
            }
            else if(choice==1)homePage();
            else if (choice==2)pharmaMain(); 
        } else {
            printf("Incorrect passkey. Try again.\n");
            attempts++;
        }
    }

    printf("Access denied. Too many failed attempts.\n");
    exit(-1);
}
