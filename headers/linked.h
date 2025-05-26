#ifndef LLC_H
#define LLC_H

typedef struct list{
    struct patient *pat;
    struct list *next;
}list;

void insertList(list **patHead, patient *pat);
void deleteList(list **patHead, patient *pat);


#endif
