#include "graph.h"

#ifndef PRIORITY_Q
#define PRIORITY_Q

typedef struct priorityQueue{
    pnode nodeData;
    int priority;
    struct priorityQueue *next;
}P_Q ,*PriorityQ;

PriorityQ createQ(pnode nodeData, int weight);
pnode peek(PriorityQ* head);
int delete(PriorityQ* head);
int insert(PriorityQ* head, pnode nodeData, int p);
int isEmpty(PriorityQ* head);