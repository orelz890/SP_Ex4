#include "graph.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "priorityQueue.h"

// Function to Create A New Node
PriorityQ createNode(pnode nodeData){
    PriorityQ temp = (PriorityQ)malloc(sizeof(P_Q));
    temp->nodeData = nodeData;
    temp->next = NULL;
    temp->prev = NULL;
 
    return temp;
}
 
// Return the value at head
PriorityQ peek(PriorityQ* head){
    if ((*head) == NULL){
        return NULL;
    }
    PriorityQ currNode = *head;
    PriorityQ highestPriority = currNode;
    while (currNode != NULL){
        if (currNode->nodeData->weight < highestPriority->nodeData->weight){
            highestPriority = currNode;
        }
        currNode = currNode->next;
    }
    // If ture it means the highestPriority is the first element.
    return highestPriority;
}
 
int delete(PriorityQ* head, PriorityQ highestPriority){
    // If ture it means the highestPriority is the first element.
    if (highestPriority->prev == NULL){
        head = &((*head)->next);
        (*head)->prev = NULL;
        free(highestPriority);
    }
    else{
        (highestPriority->prev)->next = highestPriority->next;
        (highestPriority->next)->prev = highestPriority->prev;
        free(highestPriority);
    }
    return 0;
}
 
// Function to push according to priority
int insert(PriorityQ* head, pnode nodeData){
    // Create new Node
    PriorityQ temp = createNode(nodeData);
    if(*head != NULL){
        (*head)->prev = temp;
        temp->next = *head;
    }
    head = &temp;
    return 0;
}

int isEmpty(PriorityQ* head){
    return (*head) == NULL;
}
 

