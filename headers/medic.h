#ifndef MEDIC_H
#define MEDIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {

  int day,month,year;
} date;

typedef struct{

  int id;

  char name[50];

  date mfg,expiry;

  int price;

  int stock;

}medicine;


date sys_date(void);

int rand_order(void);

#endif // MEDIC_H
