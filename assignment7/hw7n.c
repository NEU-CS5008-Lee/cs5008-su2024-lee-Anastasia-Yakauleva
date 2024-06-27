// name: Anastasia
// email: yakauleva.a@northeastern.edu

// Hash table with doubly linked list for chaning/
#include <stdio.h>
#include <stdlib.h> 

struct bucket* hashTable = NULL; 
int BUCKET_SIZE = 10; 

// node struct
struct node {

    int key;
    int value;
    struct node* next;
    struct node* prev;

};

// bucket struct
struct bucket{

    struct node* head;

};

// create a new node
struct node* createNode(int key, int value){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

//  hash function with mod
int hashFunction(int key){
    return key % BUCKET_SIZE;
}

//  insert a new key
void add(int key, int value){
    int hashIndex = hashFunction(key);
    
    struct node* newNode = createNode(key, value);

    // If the bucket is empty, insert the new node as the head
    if(hashTable[hashIndex].head == NULL){
        hashTable[hashIndex].head = newNode;

    }
    // If the bucket is not empty, insert the new node at the head of the list
    else{
        newNode-> next = hashTable[hashIndex].head;
        hashTable[hashIndex].head->prev = newNode;
        hashTable[hashIndex].head = newNode;
    }

}

// remove a key
void remove_key(int key) {
    int hashIndex = hashFunction(key);
    struct node* node = hashTable[hashIndex].head;

    // Traverse the linked list to find the node with the given key
    while (node != NULL) {
        if (node->key == key) {
            // If node to be removed is the head
            if (node->prev == NULL) {
                hashTable[hashIndex].head = node->next;
                if (node->next != NULL) {
                    node->next->prev = NULL;
                }
            } else {
                if (node->next != NULL) {
                    node->next->prev = node->prev;
                }
                node->prev->next = node->next;
            }
            free(node); // Free memory
            printf("\n[ %d ] is removed.\n", key);
            return;
        }
        node = node->next;
    }
    printf("\n[ %d ] is not found.\n", key);
}

// search a value using a key
void search(int key){
    int hashIndex = hashFunction(key);
    struct node* node = hashTable[hashIndex].head;

    // Traverse the linked list to find the node with the given key
    while(node != NULL){
        if (node->key == key){
            printf("\nKey %d is found with value %d.\n", key, node-> value);
            return;
        }
        node = node->next;
    }
    printf("\nKey %d is not found.\n", key);

}

void display(){
    struct node* iterator;

    printf("\n========= display start ========= \n");
    for (int i = 0; i<BUCKET_SIZE; i++){
        iterator = hashTable[i].head;
        printf("Bucket[%d] : ", i);
        while (iterator != NULL)
        {
            printf("(key: %d, val: %d)  <-> ", iterator->key, iterator->value);
            iterator = iterator->next;
        }
        printf("\n");
    }
    printf("\n========= display complete ========= \n");
}

int main(){
    hashTable = (struct bucket *)malloc(BUCKET_SIZE * sizeof(struct bucket));
    
    add(0, 1);
    add(1, 10);
    add(11, 12);
    add(21, 14);
    add(31, 16);
    add(5, 18);
    add(7, 19);

    display();

    remove_key(31);
    remove_key(11);

    display();

    search(11);
    search(1);
}
