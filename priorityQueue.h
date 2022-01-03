#include "graph.h"

typedef struct priorityQueue{
    pnode nodeData;
    struct priorityQueue *prev;
    struct priorityQueue *next;
}P_Q ,*PriorityQ;

PriorityQ createNode(pnode nodeData);
PriorityQ peek(PriorityQ head);
PriorityQ delete(PriorityQ head, PriorityQ highestPriority);
PriorityQ insert(PriorityQ head, pnode nodeData);
int isEmpty(PriorityQ head);