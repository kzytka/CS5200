#include "pq.h"

#include <stdlib.h>

typedef struct node node;
struct node {
    double key;
    void *value;
    struct node *next;
};

typedef struct pq pq;
struct pq {
  node *ptr;
};

/* Create a node */
node* create_node(double key, void *value){
    node* newNode = (node*)malloc(sizeof(node));
    if(newNode != NULL){
        newNode->key = key;
        newNode->value = value;
        newNode->next = NULL;
    }
    return newNode;
}

/* Allocates and initializes a new pq */
pq* pq_create(){
    pq* newPq = (pq*)malloc(sizeof(pq));
    if(newPq != NULL){
        newPq->ptr = NULL;
    }
    return newPq;
}

/* Adds value to pq based on numerical order of key */
void pq_push(pq *head, double key, void *value){
    node *newNode = create_node(key, value);
    if(newNode == NULL){
        return;
    }

    //create two nodes
    node *current = head->ptr;
    node *prev = NULL;

    //if this is the first node
    if(current == NULL){
        newNode->next = head->ptr;
        head->ptr = newNode;
    }
    else{
        //find the position
        while(current != NULL && current->key < key){
            prev = current;
            current = current->next;
        }
        //replace a middle node
        if(prev != NULL || current->key < newNode->key){
            newNode->next = current;
            prev->next = newNode;
        }
        //replace the first node
        else{
            newNode->next = head->ptr;
            head->ptr = newNode;
        }
    }

}

/* Returns value from pq having the minimum key */
void* pq_pop(pq *head){
    if(head->ptr == NULL){
        return NULL;
    }

    node *temp = head->ptr;
    void *value = temp->value;
    head->ptr = temp->next;
    free(temp);
    return value;
}

/* Deallocates (frees) pq. Shallow destruction,
meaning nodes in the pq are not recursively freed. */
void pq_destroy(pq *head){
    free(head);
}