#ifndef STACK_H     
#define STACK_H



typedef struct stack{
   struct patient *patient;
   struct stack *next;

}stack;



stack* createStack(stack **top);

void push(stack **top,struct patient *patient);
void pop(stack **top);













#endif
