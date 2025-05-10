#include "../headers/doctors.h"
#include "../headers/treeDoc.h"
#include "../headers/departments.h"
#include "../headers/queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void createQueue(Queue* doctorQueue) {
    doctorQueue->front = NULL;
    doctorQueue->rear = NULL;
}
void enqueue (Queue* doctorQueue,patient* patient,doctor* doctor){
    if (doctorQueue == NULL || patient == NULL) {
        printf("could not add patient to queue\n");
        return; // Handle error
    }
    node *newNode=(node*)malloc(sizeof(node));
    newNode->patient=patient;
    newNode->next=NULL;
    if(doctorQueue->front==NULL){
        doctorQueue->front=newNode;
        doctorQueue->rear=newNode;}
     else{
            doctorQueue->rear->next=newNode;
            doctorQueue->rear=newNode;
     }
    printf("patient %s added to queue of the doctor %s\n",patient->name,doctor->name);
}
patient* dequeue(Queue *q) {
    if (q->front == NULL) return NULL;

    node *temp = q->front;
    patient *p = temp->patient;

    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;

    free(temp);
    return p;
}


int isEmpty(Queue* queue) {
    return (queue->front == NULL); // 1 = true (empty), 0 = false (not empty)
}

void freeQueue(Queue *q) {
    while (q->front != NULL) {
        node *temp = q->front;
        q->front = q->front->next;

        if (temp->patient != NULL) {
            free(temp->patient);  // only if not freed in dequeue
        }

        free(temp);
    }
    free(q);
}

void displayDoctorSchedule(Queue *q) {
    if (q == NULL || q->front == NULL) {
        printf("No patients in the schedule.\n");
        return;
    }

    node *current = q->front;
    int index = 1;
    while (current != NULL) {
        printf("Patient %d: %s\n", index++, current->patient->name);
        current = current->next;
    }
}