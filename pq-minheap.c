#include "pq.h"

#include <stdlib.h>

typedef struct node node;
struct node {
    double key;
    void *value;
    struct node *left;
    struct node *right;
    struct node *parent;
};

typedef struct pq pq;
struct pq {
  node *ptr;
};

/* Create a node */
node* create_node(double key, void *value, node *parent){
    node* newNode = (node*)malloc(sizeof(node));
    if(newNode != NULL){
        newNode->key = key;
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = parent;
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

void storeArray(node* root, node** array, int* index){
    if(root == NULL){
        return;
    }
    storeArray(root->left, array, index);
    array[(*index)++] = root;
    storeArray(root->right, array, index);
}

int compare(const void *a, const void *b){
    node* node1 = *(node**)a;
    node* node2 = *(node**)b;

    if(node1->key < node2->key){
        return -1;
    }
    else if(node1->key > node2->key){
        return 1;
    }
    else{
        return 0;
    }
}

/* Adds value to pq based on numerical order of key */
void pq_push(pq *head, double key, void *value){
    node *newNode = create_node(key, value, NULL);
    if(newNode == NULL){
        return;
    }

    //create two nodes
    node *current = head->ptr;
    node *prev = NULL;

    //create root node
    if(current == NULL){
        head->ptr = newNode;
    }
    else{
        //where to put it
        while(current != NULL){
            prev = current;

            //which side to go down
            if(key < current->key){
                current = current->left;
            }
            else{
                current = current->right;
            }
        }

        //which side to put in on
        if(key < prev->key){
            prev->left = newNode;
        }
        else{
            prev->right = newNode;
        }

        //add parent
        newNode->parent = prev;

        //check if it is the lower than its parent and change accordingly
        while(newNode != head->ptr && newNode->key < newNode->parent->key){
            double tempKey = newNode->key;
            void* tempVal = newNode->value;

            newNode->key = newNode->parent->key;
            newNode->value = newNode->parent->value;

            newNode->parent->key = tempKey;
            newNode->parent->value = tempVal;

            newNode = newNode->parent;
        }
    }
}

/* Returns value from pq having the minimum key */
void* pq_pop(pq *head){
    if(head->ptr == NULL && head == NULL){
        return NULL;
    }
    else{
        node *minimum = head->ptr;

        node *current = head->ptr;
        while(current->left != NULL || current->right != NULL){
            if(current->right != NULL){
                if(current->left != NULL){
                    if(current->right->key < current->left->key){
                        current = current->right;
                    }
                    else{
                        current = current->left;
                    }
                }
                else{
                    current = current->right;
                }
            }
            else{
                current = current->left;
            }
        }

        double tempKey = head->ptr->key;
        void* tempVal = head->ptr->value;

        head->ptr->key = current->key;
        head->ptr->value = current->value;

        current->key = tempKey;
        current->value = tempVal;

        if(current->parent != NULL){
            if(current == current->parent->left){
                current->parent->left = NULL;
            }
            else{
                current->parent->right = NULL;
            }
        }

        free(current);
        return minimum->value;
    }

}

/* Deallocates (frees) pq. Shallow destruction,
meaning nodes in the pq are not recursively freed. */
void pq_destroy(pq *head){
    free(head);
}