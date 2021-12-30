#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;
static int gSize = 0

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    int flag;
    double weight;
    int edgeSize;
    pedge edges;
    struct GRAPH_NODE_ *next;
    struct GRAPH_NODE_ *prev;

} node, *pnode;

void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);
int addNode(pnode *head, pnode currNode,int id);
int removeNode(pnode *head, int id);

#endif
