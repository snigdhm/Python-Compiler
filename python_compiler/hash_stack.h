#include <stdio.h>
#include <stdlib.h>
#include "hash_table.c"

typedef struct stackt
{
    int size;
    int width;
    hashtable_t** data;
} STACK1;
 
void initStack1(STACK1* stack, int size);
hashtable_t* pop1(STACK1* stack);
void push1(STACK1* stack, hashtable_t* val);
hashtable_t* peek1(STACK1* stack);
hashtable_t* elementAt(STACK1* stack,int i);
//void printStack(STACKH* stack);

