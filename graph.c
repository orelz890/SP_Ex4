#include <math.h> 
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

static pnode graph;

void build_graph_cmd(pnode *head){
    if (graph != NULL){
        deleteGraph_cmd();
    }
    char c;
    scanf("%c",&c);
    int nodesNum = c - '0';
    for (size_t i = 0; i < nodesNum; i++){
        pnode currNode = (pnode) malloc(sizeof(node)); // need to free!!!
        addNode(head,currNode,i);

    } 
}

void insert_node_cmd(pnode *head){
    
}
int addEdge(pnode *node,int nodeId){


    return 0;
}

int addNode(pnode *head, pnode currNode,int id){
    currNode->node_num = id;
    currNode->edges = NULL;
    currNode->next = NULL;
    currNode->prev = NULL;
    currNode->weight = INFINITY;
    currNode->flag = 0;
    currNode->edgeSize = 0;
    
    node tempNode = *head;
    if (tempNode != NULL){    
        while (tempNode.next != NULL){
            pnode nextNode = tempNode.next;
            nextNode.prev = tempNode;
            tempNode.next = nextNode;
        }
        tempNode.next = currNode;
        currNode.prev = tempNode;
    }else{
        head = &currNode;
    }
    gSize += 1;
    return 0;
}

void delete_node_cmd(pnode *head){
    char c;
    scanf("%c",&c);
    int id = c - '0';
    removeNode(head, id);
}

int removeNode(pnode *head, int id){
    // Erasing all the edges that there dest is this node.
    node nodeToRemove = NULL;
    node tempNode = *head;
    pedge currEdges = tempNode.edges;
    while (tempNode != NULL){
        if (tempNode.node_num == id){
            nodeToRemove = tempNode;
        }
        edge tempEdge = *(tempNode.edges);
        while (tempEdge != NULL){
            edge nextEdge = tempEdge.next;
            if (tempEdge.endpoint.node_num == id){
                free(tempEdge);
            }
            tempEdge = nextEdge;
        }
        tempNode = tempNode->next;
    }
    // Erasing this node edges and itself.
    edge tempEdge = *(nodeToRemove.edges);
    while (tempEdge != NULL){
        edge nextEdge = tempEdge.next;
        free(tempEdge);
        tempEdge = nextEdge;
    }
    if (nodeToRemove.prev != NULL){
        nodeToRemove.prev->next = nodeToRemove.next;
    }
    nodeToRemove.next->prev = nodeToRemove.prev;
    nodeToRemove.prev->next = nodeToRemove.next;
    free(nodeToRemove);
    gSize -= 1;
    return 0;
}
//for self debug
void printGraph_cmd(pnode head){

}

void deleteGraph_cmd(pnode* head){
    // Erasing all the edges to this node
    node tempNode = *head;
    while (tempNode != NULL){
        node nextNode = tempNode->next;
        edge currEdges = *(tempNode.edges);
        while (currEdges != NULL){
            edge nextEdge = currEdges.next;
            free(currEdges);
            currEdges = nextEdge;
        }
        free(tempNode);
        tempNode = nextNode;
    }
}

void shortsPath_cmd(pnode head){

}

void TSP_cmd(pnode head){

}