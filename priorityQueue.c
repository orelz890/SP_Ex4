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
PriorityQ peek(PriorityQ head){
    if (head == NULL){
        return NULL;
    }
    PriorityQ currNode = head;
    // printf("current node is  %d\n",currNode->nodeData->node_num);
    // fflush(NULL);
    PriorityQ highestPriority = currNode;
    while (currNode != NULL){
        if (currNode->nodeData->weight < highestPriority->nodeData->weight){
            highestPriority = currNode;
        }
        currNode = currNode->next;
    }
    // printf("return node %d\n",highestPriority->nodeData->node_num);
    // fflush(NULL);
    // If ture it means the highestPriority is the first element.
    return highestPriority;
}
 
int delete(PriorityQ head, PriorityQ highestPriority){
    // If ture it means the highestPriority is the first element.
    int higest = highestPriority->nodeData->node_num;
    if (highestPriority != NULL){
        if (highestPriority->prev == NULL){
            // printf("im1 %d in proccess\n",higest);
            // fflush(NULL);
            head = head->next;
            // printf("im2 %d in proccess\n",higest);
            // fflush(NULL);
            if (head != NULL){
                if(head->prev != NULL){
                    // printf("im3 %d in proccess\n",higest);
                    // fflush(NULL);
                    head->prev = NULL;
                    // printf("im4 %d in proccess\n",higest);
                    // fflush(NULL);
                }
            }
            // printf("im5 %d in proccess\n",higest);
            // fflush(NULL);
            free(highestPriority);
            // printf("im6 %d in proccess\n",higest);
            // fflush(NULL);
        }
        else{
            if (highestPriority->prev != NULL){
                (highestPriority->prev)->next = highestPriority->next; 
            }
            if (highestPriority->next != NULL){
                (highestPriority->next)->prev = highestPriority->prev;
            }
            // printf("im here2 %d in proccess\n",higest);
            // fflush(NULL);
            free(highestPriority);
        }
    }
    // printf("node %d deleted\n",higest);
    // fflush(NULL);
    return 0;
}
 
// Function to push according to priority
PriorityQ insert(PriorityQ head, pnode nodeData){
    // Create new Node
    PriorityQ temp = createNode(nodeData);
    if(head != NULL){
        head->prev = temp;
        temp->next = head;
    }
    head = temp;
    // printf("%p,%d\n",temp,temp->nodeData->node_num);
    // fflush(NULL);
    return head;
}

int isEmpty(PriorityQ head){
    return head == NULL || head->nodeData->node_num < 0 || head->nodeData->weight < 0;
}
 

