#include "hash_stack.h"
 
void initStack1(STACK1* stack, int size)
{
    stack->width = size;
    stack->size = 0;
    stack->data = (hashtable_t**)calloc(size,sizeof(hashtable_t));
   
}
 
hashtable_t* pop1(STACK1* stack)
{
   if (stack->size > 0)
   {
       stack->size--;
       return stack->data[stack->size];
   }
}
 
void push1(STACK1* stack, hashtable_t* val)
{
    if (stack->size >= stack->width / 2)
    {
        stack->width = stack->width * 2;
        stack->data = realloc(stack->data, stack->width);
    }
 
    stack->data[stack->size] = val;
    stack->size++;
}
 
hashtable_t* peek1(STACK1* stack)
{
    if (stack->size > 0)
    {
        hashtable_t* val = stack->data[stack->size - 1];
        return val;
    }
}

hashtable_t* peek1at(STACK1* stack,int i)
{
    if (stack->size > 0 && stack->size>i)
    {
        hashtable_t* val = stack->data[i];
        return val;
    }
}
 
/*void printStack(STACK1* stack)
{
    int i;
    for (i = 0; i < stack->size; i++)
    {
        printf("%d: %d\n", i, stack->data[i]);
    }
}*/

hashtable_t* elementAt(STACK1* stack,int i)
{
    int j;
    for (j = 0; j < stack->size; j++)
    {
		if(j==i)
        return stack->data[i];
    }
}
/*int main()
{
  STACK indent;
  initStack(&indent,1);
  push(&indent,1);
  push(&indent,2);
  printStack(&indent);
  return 0;

}*/

