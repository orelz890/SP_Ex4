#include "graph.h"
typedef struct List{
    pnode nodeData;
    struct List *prev;
    struct List *next;
    struct List *tail;
}ListHead ,*List;

List listCreateNode(pnode nodeData);
List listPeek(List head, int id);
List listRemove(List head, int id);
List listInsert(List head, pnode nodeData);
int listIsEmpty(List head);
List list_clone(List head);