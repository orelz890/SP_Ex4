#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include "priorityQueue.h"

// Aided by this site: https://www.geeksforgeeks.org/priority-queue-using-linked-list/

// Function to Create A New Node
PriorityQ createQ(pnode nodeData, int weight){
    PriorityQ temp = (PriorityQ)malloc(sizeof(P_Q));
    temp->nodeData = nodeData;
    temp->priority = weight;
    temp->next = NULL;
 
    return temp;
}
 
// Return the value at head
int peek(PriorityQ* head){
    return (*head)->data;
}
 
// Removes the element with the
// highest priority form the list
int delete(PriorityQ* head){
    PriorityQ temp = *head;
    (*head) = (*head)->next;
    free(temp);
    return 0;
}
 
// Function to push according to priority
int insert(PriorityQ* head, pnode nodeData, int p){
    PriorityQ start = (*head); 
    // Create new Node
    PriorityQ temp = createQ(nodeData, p);

    if ((*head)->priority > p) {
        // Insert New Node before head
        temp->next = *head;
        (*head) = temp;
    }
    else {
        while (start->next != NULL && start->next->priority < p) {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
    return 0;
}

int isEmpty(PriorityQ* head){
    return (*head) == NULL;
}
 

