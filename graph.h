#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;
static int gSize = 0

typedef struct edge_ {
    int weight;
    struct GRAPH_NODE_ *endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    int flag;
    double weight;
    int edgeSize;
    struct edge_* edges;
    struct edge_ tail;
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
int addNode(pnode *head, pnode currNode,int id);
int addEdge(pnode* head, pnode node, int dest, int weight);
int removeNode(pnode *head, int id);
node findNode(pnode *head,int id);
pedge findEdge(pnode currNode ,int dest);
char creatAllGivenEdges(pnode *head,node existingNode);
char getValidChar();

#endif
