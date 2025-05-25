#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "medic.h"
#include "pharm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char name[20];
    char email[30];
    char phone[11];
    char password[11];
} customer;

void buy(medicine *ptr, char fname_customer[], int cart_count);
void account_customer(void);
int login_customer(char fname[]);
int no_sellers(void);
void add_cart(medicine *ptr, int no_sellers, char **sellers, int id, int quantity, int cart_count);
void print_cart(medicine *ptr, int cart_count);
void delete_cart(medicine *ptr, int no_sellers, char **sellers, int id, int quantity, medicine *ptr1, int cart_count, int new_cart_count);

#endif // CUSTOMER_H
