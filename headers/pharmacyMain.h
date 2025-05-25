#ifndef HOSPITAL_PHARMACY_H
#define HOSPITAL_PHARMACY_H

#include <stdio.h>

// ---------- Medicine Structure ----------
typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} medicine;

// ---------- Pharmacist Functions ----------
int login_pharmacist(char *login);
void account_pharmacist();
void add_drug(char *pharmacist_name);
void delete_drug(char *pharmacist_name);
void update_drug(char *pharmacist_name);
void print_stock(char *pharmacist_name);
void alert(char *pharmacist_name);
void pharmaMain();
// ---------- Customer Functions ----------
int login_customer(char *login);
void account_customer();
int no_sellers();

// ---------- Cart Functions ----------
void add_cart(medicine *cart, int seller_count, char **sellers, int drug_id, int quantity, int index);
void delete_cart(medicine *cart, int seller_count, char **sellers, int drug_id, int quantity, medicine *new_cart, int old_count, int new_count);
void print_cart(medicine *cart, int cart_count);
void buy(medicine *cart, char *customer_name, int cart_count);

#endif // HOSPITAL_PHARMACY_H
