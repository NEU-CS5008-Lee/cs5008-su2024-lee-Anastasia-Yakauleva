//Anastasia
//yakauleva.a@northeastern.edu

#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
    int data;
    struct node *next;
}node_t;

typedef struct list{
    struct node* head;
}List;

/*-----creating the nodes----------*/
node_t* newNode(int num)
{
    node_t *newNode = (node_t*)malloc(sizeof(node_t));
    if (newNode == NULL){
        printf("Memory allocation failed");
        exit(1);
    }
    newNode->data = num;
    newNode->next = NULL;
    return newNode;
 
}
/*---creating linked list----*/
List* init_LL(){
    List* list = (List*)malloc(sizeof(List));
    if (list == NULL){
        printf("Memory allocation failed");
        exit(1);
    }
    list->head = NULL;
    return list;
    
}

/*---Insert the nodes at the begining of the list---*/
void insertFirst(List* l, int data){
    node_t* firstNode = newNode(data);
    if (l->head == NULL){ //if our list is empty
        l->head = firstNode;
        return;
    }
    firstNode->next = l->head;
    l->head = firstNode;
    return;

}

/*----display the output--------*/
void display(List* l)
{
    node_t *temp;
    temp=l->head;
    while(temp!=NULL)
    {
        printf("%d->",temp->data);
        temp=temp->next;
    }
    printf("NULL\n");
}

/*-------reversing the linked list using recursion------*/
void reverse(List* l, node_t* ptr)
{
    // if the list is empty, return without doing anything.
    if(l->head == NULL) {
        return;
    }

    // Base case: if it is the last node
    if(ptr->next == NULL) {
        l->head = ptr; // the last node of the orig lst becomes the head
        return;
    }

    // Recursive case
    reverse(l, ptr->next);

    ptr->next->next = ptr; // loop pointers of current and next el
    ptr->next = NULL; // beak pointers loop and set current node point to 0
    
}

/*----Free the nodes-----*/
void freenode(List* l){
  node_t *temp;
    while(l->head)
    {
        temp=l->head->next;
        free(l->head);
        l->head=temp;
    }  
    
}
/*-----Main program--------------*/
int main()
{
    List *list=init_LL();
    

    insertFirst(list,44);
    insertFirst(list,33);
    insertFirst(list,22);
    insertFirst(list,11);
    display(list);
    reverse(list,list->head);
    display(list);
    
    freenode(list);
    free(list);
    return 0;
}
