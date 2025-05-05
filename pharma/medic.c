#include"medic.h"

date sys_date(void){
    date sys_date;
    time_t t = time(NULL);
    struct tm tm;
    tm = *localtime(&t);
    sys_date.day = tm.tm_mday;
    sys_date.month = tm.tm_mon + 1;
    sys_date.year = tm.tm_year + 1900;
    return sys_date;
}
int rand_order(void){
    srand(time(0));  // Generate a random order number between 0 and 999
    int order = rand() % 1000;
    return order;
}

