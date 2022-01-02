#include "graph.h"

typedef struct priorityQueue{
    pnode nodeData;
    int priority;
    struct priorityQueue *prev;
    struct priorityQueue *next;
}P_Q ,*PriorityQ;

PriorityQ createNode(pnode nodeData, int weight);
PriorityQ peek(PriorityQ* head);
int delete(PriorityQ* head, PriorityQ highestPriority);
int insert(PriorityQ* head, pnode nodeData, int p);
int isEmpty(PriorityQ* head);