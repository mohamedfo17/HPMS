
#include "../headers/resources.h"
#include <stdlib.h>
#include <stdio.h>



int checkRange(int number,int start,int end){
    if (number<=end||number>=start)
    {
        return 1;
    }
    return 0;
};
