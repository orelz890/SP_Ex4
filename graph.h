#ifndef GRAPH_
#define GRAPH_
static int gSize = 0;

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
}edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    int tag;
    double weight;
    int edgeSize;
    pedge edges;
    pedge tail;
    struct GRAPH_NODE_ *next;
    struct GRAPH_NODE_ *prev;

} node, *pnode;

char build_graph_cmd(pnode *head);
char insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);
pnode addNode(pnode *head, pnode currNode,int id);
int addEdge(pnode* head, pnode node, int dest, int weight);
int removeNode(pnode *head, int id);
pnode findNode(pnode *head,int id);
pedge findEdge(pnode currNode ,int dest);
char creatAllGivenEdges(pnode *head,pnode existingNode);
char getValidChar();

#endif