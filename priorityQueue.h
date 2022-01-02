#include "graph.h"

typedef struct priorityQueue{
    pnode nodeData;
    struct priorityQueue *prev;
    struct priorityQueue *next;
}P_Q ,*PriorityQ;

PriorityQ createNode(pnode nodeData);
PriorityQ peek(PriorityQ* head);
int delete(PriorityQ* head, PriorityQ highestPriority);
int insert(PriorityQ* head, pnode nodeData);
int isEmpty(PriorityQ* head);