// name: Anastasia Yakauleva
// email: yakauleva.a@northeastern.edu

#include <stdio.h>   // stardard input/output library
#include <stdbool.h> // standard boolean library: bool, true,

#define MAXSIZE 100

bool isEmpty (int top) {
  // returns true if top = -1

  if (top == -1){
    return true;
  } else {
    return false;
  }
}

bool isFull (int top) {
  // returns true if no more room in the stack

  if (top >= MAXSIZE - 1){
    return true;
  } else {
    return false;
    }

}

void push(int v, int* pStack, int* pTop) {
  // put v onto the top of the stack s unless it is already full

  if (!isFull(*pTop)) {
    (*pTop)++;
    pStack[*pTop] = v;
  } else {
    printf("*** Attempt to push full stack***\n");
  }
  return;
}

int pop (int* pStack, int* pTop) {
  // return the top entry in the stack unless stack is empty
  // update s and *top -- requires top to be passed by reference!
  int returnval = 0;

  if (!isEmpty(*pTop)) {
    returnval = pStack[*pTop];
    (*pTop)--;  // Decrement top to update it
  } else {
    printf("***Attempt to pop empty stack***\n");
  }
  return returnval;
}

int main () {

  int stack1[MAXSIZE]; // array in which stack will live
  int top1 = -1;       // top valid location in stack, -1 == empty
  int stack2[MAXSIZE]; // array in which stack will live
  int top2 = -1;       // top valid location in stack, -1 == empty
  
  printf("pushing: 1, 2, 3, 4, 5 onto first stack\n");
  printf("pushing: 100, 200, 300, 400, 500 onto second stack\n\n");
  push(1, stack1, &top1);
  push(2, stack1, &top1);
  push(3, stack1, &top1);
  push(4, stack1, &top1);
  push(5, stack1, &top1);
  push(100, stack2, &top2);
  push(200, stack2, &top2);
  push(300, stack2, &top2);
  push(400, stack2, &top2);
  push(500, stack2, &top2);

  printf("popping alternating stacks:\n");
  printf("1> %d\n",pop(stack1, &top1));
  printf("2> %d\n",pop(stack2, &top2));
  printf("1> %d\n",pop(stack1, &top1));
  printf("2> %d\n",pop(stack2, &top2));
  printf("1> %d\n",pop(stack1, &top1));
  printf("2> %d\n",pop(stack2, &top2));
  printf("1> %d\n",pop(stack1, &top1));
  printf("2> %d\n",pop(stack2, &top2));
  printf("1> %d\n",pop(stack1, &top1));
  printf("2> %d\n",pop(stack2, &top2));
  printf("1> %d\n",pop(stack1, &top1));
  printf("2> %d\n",pop(stack2, &top2));
  return 0;
}
