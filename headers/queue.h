#ifndef QUEUE_H     
#define QUEUE_H

typedef struct node {
  struct  patient *patient;
    struct node* next;
} node;

typedef struct Queue {
    node* front;
    node* rear;
} Queue;


void createQueue(Queue* doctorQueue);
void enqueue(Queue* doctorQueue,struct patient* patient,struct doctor* doctor);
struct patient* dequeue(Queue* doctorQueue);
int isEmpty(Queue* doctorQueue);
void freeQueue(Queue *q);
void displayDoctorSchedule(Queue *q);
void deletefromqueue(Queue *q, char id[15]);







#endif