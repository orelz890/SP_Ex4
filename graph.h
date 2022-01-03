#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
}edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    int weight;
    int edgeSize;
    pedge edges;
    pedge tail;
    struct GRAPH_NODE_ *next;
    struct GRAPH_NODE_ *prev;
    struct GRAPH_NODE_ *perent;

} node, *pnode;

char build_graph_cmd();
char insert_node_cmd();
void delete_node_cmd();
void printGraph_cmd(); //for self debug
void deleteGraph_cmd();
int shortsPath_cmd(int src, int dest);
int TSP_cmd(int num);
pnode addNode(pnode currNode,int id);
void addEdge(pnode node, int dest, int weight);
int removeNode(int id);
pnode findNode(int id);
pedge findEdge(pnode currNode ,int dest);
char creatAllGivenEdges(pnode existingNode);
char getValidChar();
int dijkstra(int src);

#endif