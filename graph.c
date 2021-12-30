#include <math.h> 
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

static pnode graph;

char build_graph_cmd(pnode *head){
    if (graph != NULL){
        deleteGraph_cmd();
    }
    char c = getValidChar();
    int nodesNum = c - '0';
    for (size_t i = 0; i < nodesNum; i++){
        pnode currNode = (pnode) malloc(sizeof(node)); // need to free!!!
        addNode(head,currNode,i);
    }
    char currChar = getValidChar();
    while (currChar == 'n'){
        char currNode = getValidChar();
        currChar = creatAllGivenEdges(head,findNode(head,(currChar - '0')));
    }
    return currChar;    
}

char insert_node_cmd(pnode *head){
    char c = getValidChar();
    int id = c -'0';
    node existingNode = *(findNode(head,id));
    if (existingNode != NULL){
        edge currEdge = *(existingNode.edges);
        while (currEdge != NULL){
            edge nextEdge = *(currEdge.next);
            free(currEdge);
            currEdge = nextEdge;
        }
    }else{
        pnode currNode = (pnode) malloc(sizeof(node)); // need to free!!!
        existingNode = *(addNode(head,currNode,id));
    }
    return creatAllGivenEdges(head,existingNode);
}

char creatAllGivenEdges(pnode *head,node existingNode){
    char first;
    char sec;
    scanf("%c",first);
    int dest = first - '0';
    while (dest >= 0 && dest <= 9){
        scanf("%c",sec);
        int weight = sec - '0';
        addEdge(head,&existingNode,dest,weight);
        scanf("%c",first);
        dest = first - '0';
    }
    return first;
}

pnode findNode(pnode *head,int id){
    node existingNode = NULL;
    node tempNode = *(*head);
    while (tempNode != NULL){
        node nextNode = *(tempNode.next);
        if (tempNode.node_num == id){
            return tempNode;
        }
        tempNode = nextNode;
    }
    return NULL;
}

pedge findEdge(pnode currNode ,int dest){
    pedge edges = currNode->edges;
    edge tempEdge = *(edges);
    while (tempEdge != NULL){
        if (tempEdge.endpoint->node_num == dest){
            return &tempEdge;
        }
        tempEdge = *(tempEdge.next);
    }
    return NULL;
}

int addEdge(pnode* head, pnode node, int dest, int weight){

    pedge existingEdge = findEdge(node,dest);
    if (existingEdge != NULL){
        existingEdge->weight = weight;
    }
    else{
        pedge newEdge = (pedge) malloc(sizeof(edge)); // need to free!!!
        newEdge->weight = weight;
        newEdge->endpoint = findNode(head,dest);
        newEdge->next = NULL;
        if (node->edges == NULL){
            node->edges = &newEdge;
        }
        if ((node->tail).next != NULL){
            (node->tail).next = newEdge;
        }
        node->tail = *(newEdge);
        node->edgeSize += 1;
    }
    return 0;
}

pnode addNode(pnode *head,pnode currNode,int id){
    currNode->node_num = id;
    currNode->edges = NULL;
    currNode->tail = NULL;
    currNode->next = NULL;
    currNode->prev = NULL;
    currNode->weight = INFINITY;
    currNode->flag = 0;
    currNode->edgeSize = 0;
    
    node tempNode = *(*head);
    if (tempNode != NULL){    
        while (tempNode.next != NULL){
            // If the a node with that ip already exist retun it.
            if (tempNode.node_num == id){
                return tempNode;
            }
            tempNode = *(tempNode.next)
        }
        tempNode.next = currNode;
        currNode.prev = tempNode;
    }else{
        head = &currNode;
    }
    gSize += 1;
    return currNode;
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
    node tempNode = *(*head);
    int flag = 0;
    while (tempNode != NULL){
        if (tempNode.node_num == id){
            nodeToRemove = tempNode;
        }
        edge tempEdge = *(tempNode.edges);
        edge prevEdge = NULL;
        while (tempEdge != NULL){
            edge nextEdge = *(tempEdge.next);
            if (tempEdge.endpoint->node_num == id){
                free(tempEdge);
                tempNode.edgeSize -= 1;
                flag = 1;
            }
            if (flag == 0){
                prevEdge = tempEdge;
            }
            else if (prevEdge != NULL){
                prevEdge.next = &nextEdge;
                flag = 0;
            }
            tempEdge = nextEdge;
        }
        tempNode.tail = tempEdge;
        tempNode = tempNode.next;
    }
    // Erasing this node edges and itself.
    edge tempEdge = *(nodeToRemove.edges);
    while (tempEdge != NULL){
        edge nextEdge = *(tempEdge.next);
        free(tempEdge);
        tempEdge = nextEdge;
    }
    free(nodeToRemove);
    gSize -= 1;
    return 0;
}

//for self debug
void printGraph_cmd(pnode head){
    node currNode = *head;
    while (currNode != NULL){
        printf("id: %d {",currNode.node_num);
        edge currEdge = *(currNode.edges);
        while (currEdge != NULL){
            printf("(%d,%d), ",(currEdge.endpoint)->node_num, currEdge.weight);   
            currEdge = *(currEdge.next);
        }
        printf("}\n");
        currNode = *(currNode.next);
    }
}

void deleteGraph_cmd(pnode* head){
    // Erasing all the edges to this node
    node tempNode = *(*head);
    while (tempNode != NULL){
        node nextNode = *(tempNode.next);
        edge currEdge = *(tempNode.edges);
        while (currEdges != NULL){
            edge nextEdge = *(currEdge.next);
            free(currEdge);
            currEdge = nextEdge;
        }
        free(tempNode);
        tempNode = nextNode;
    }
}

void shortsPath_cmd(pnode head){

}

void TSP_cmd(pnode head){

}

char getValidChar(){
    char c;
    scanf("%c",&c);
    while (c == ' '){
        scanf("%c",&c);
    }
    return c;
    
}