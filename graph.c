#include <math.h>
#include <limits.h>
#include <string.h>
#include "graph.h"
#include "priorityQueue.h"
#include <stdio.h>
#include <stdlib.h>

#define NOPATH 1
#define WORKED 0

PriorityQ* setAllTags(PriorityQ* queue,int src);

static pnode head;

char build_graph_cmd(){
    if (head != NULL){
        deleteGraph_cmd();
    }
    printf("in here1");
    char c = getValidChar();
    printf("in here2");
    int nodesNum = c - '0';
    for (size_t i = 0; i < nodesNum; i++){
        pnode currNode = NULL;
        currNode = (pnode) malloc(sizeof(node)); // need to free!!!
        addNode(currNode,i);
    }
    printf("in here3");
    char currChar = getValidChar();
    while (currChar == 'n'){
        char currNode = getValidChar();
        currChar = creatAllGivenEdges(findNode(currNode - '0'));
    }
    printf("in here4");
    return currChar; 
}

char insert_node_cmd(){
    char c = getValidChar();
    int id = c -'0';
    pnode foundNode = findNode(id);
    pnode existingNode = foundNode;
    if (foundNode != NULL){
        pedge currEdge = existingNode->edges;
        while (currEdge != NULL){
            pedge nextEdge = currEdge->next;
            free(currEdge);
            currEdge = nextEdge;
        }
    }else{
        pnode currNode = NULL;
        currNode = (pnode) malloc(sizeof(node)); // need to free!!!
        existingNode = addNode(currNode,id);
    }
    return creatAllGivenEdges(existingNode);
}

char creatAllGivenEdges(pnode existingNode){
    char first;
    char sec;
    scanf("%c",&first);
    int dest = first - '0';
    while (dest >= 0 && dest <= 9){
        scanf("%c",&sec);
        int weight = sec - '0';
        addEdge(existingNode,dest,weight);
        scanf("%c",&first);
        dest = first - '0';
    }
    return first;
}

pnode findNode(int id){

    pnode tempNode = head;
    while (tempNode != NULL){
        pnode nextNode = tempNode->next;
        if (tempNode->node_num == id){
            return tempNode;
        }
        tempNode = nextNode;
    }
    return NULL;
}

pedge findEdge(pnode currNode ,int dest){
    pedge edgesPointer = currNode->edges;

    while (edgesPointer != NULL){
        if ((edgesPointer->endpoint)->node_num == dest){
            return edgesPointer;
        }
        edgesPointer = edgesPointer->next;
    }
    return NULL;
}

int addEdge(pnode node, int dest, int weight){

    pedge existingEdge = findEdge(node,dest);
    if (existingEdge != NULL){
        existingEdge->weight = weight;
    }
    else{
        pedge newEdge = NULL;
        newEdge = (pedge) malloc(sizeof(edge)); // need to free!!!
        newEdge->weight = weight;
        newEdge->endpoint = findNode(dest);
        newEdge->next = NULL;
        if (node->edges == NULL){
            node->edges = newEdge;
        }
        if (node->tail->next != NULL){
            node->tail->next = newEdge;
        }
        node->tail = newEdge;
        node->edgeSize += 1;
    }
    return 0;
}

pnode addNode(pnode currNode,int id){
    currNode->node_num = id;
    currNode->edges = NULL;
    currNode->tail = NULL;
    currNode->next = NULL;
    currNode->prev = NULL;
    currNode->perent = NULL;
    currNode->weight = INFINITY;
    currNode->edgeSize = 0;
    
    pnode tempNode = head;
    if (tempNode != NULL){    
        while (tempNode->next != NULL){
            // If the a node with that ip already exist retun it.
            if (tempNode->node_num == id){
                return tempNode;
            }
            tempNode = tempNode->next;
        }
        tempNode->next = currNode;
        currNode->prev = tempNode;
    }else{
        head = currNode;
    }
    gSize += 1;
    return currNode;
}

void delete_node_cmd(){
    char c;
    scanf("%c",&c);
    int id = c - '0';
    removeNode(id);
}

int removeNode(int id){
    // Erasing all the edges that there dest is this node.
    pnode nodeToRemove = NULL;
    pnode tempNode = head;
    int flag = 0;
    while (tempNode != NULL){
        if (tempNode->node_num == id){
            nodeToRemove = tempNode;
        }
        pedge tempEdge = tempNode->edges;
        pedge prevEdge = NULL;
        while (tempEdge != NULL){
            pedge nextEdge = tempEdge->next;
            if (tempEdge->endpoint->node_num == id){
                free(tempEdge);
                tempNode->edgeSize -= 1;
                flag = 1;
            }
            if (flag == 0){
                prevEdge = tempEdge;
            }
            else if (prevEdge != NULL){
                prevEdge->next = nextEdge;
                flag = 0;
            }
            tempEdge = nextEdge;
        }
        // Now temp edge is NULL therefore, prevEdge is the tail.
        tempNode->tail = prevEdge;
        tempNode = tempNode->next;
    }
    // Erasing this node edges and itself.
    pedge tempEdge = nodeToRemove->edges;
    while (tempEdge != NULL){
        pedge nextEdge = tempEdge->next;
        free(tempEdge);
        tempEdge = nextEdge;
    }
    free(nodeToRemove);
    gSize -= 1;
    return 0;
}

//for self debug
void printGraph_cmd(){
    pnode currNode = head;
    while (currNode != NULL){
        printf("id: %d {",currNode->node_num);
        pedge currEdge = currNode->edges;
        while (currEdge != NULL){
            printf("(%d,%d), ",currEdge->endpoint->node_num, currEdge->weight);   
            currEdge = currEdge->next;
        }
        printf("}\n");
        currNode = currNode->next;
    }
}

void deleteGraph_cmd(){
    // Erasing all the edges to this node
    pnode tempNode = head;
    while (tempNode != NULL){
        pnode nextNode = tempNode->next;
        pedge currEdge = tempNode->edges;
        while (currEdge != NULL){
            pedge nextEdge = currEdge->next;
            free(currEdge);
            currEdge = nextEdge;
        }
        free(tempNode);
        tempNode = nextNode;
    }
}

int dijkstra(int src){
    PriorityQ* queue = NULL;
    queue = setAllTags(queue,src);
    if(queue == NULL){
        return NOPATH;
    }
    while (isEmpty(queue) != 1){
        PriorityQ peeking = peek(queue);
        pnode temp_node = peeking->nodeData;
        delete(queue,peeking);
        pedge currEdge = temp_node->edges;
        while (currEdge != NULL){
            int new_weight = temp_node->weight + currEdge->weight;
            if (new_weight < currEdge->endpoint->weight){
                currEdge->endpoint->weight = new_weight;
                currEdge->endpoint->perent = temp_node;
            }
            currEdge = currEdge->next;  
        }
    }
    return 0;
}

PriorityQ* setAllTags(PriorityQ* queue,int src){
    pnode srcNode = findNode(src);
    if (srcNode == NULL){
        return NULL;
    }
    pnode currNode = head;
    while (currNode != NULL){
        if(currNode->node_num == src){
            currNode->weight = 0;
            currNode->perent = currNode;
        }
        else{
            currNode->weight = INT_MAX;
            currNode->perent = NULL;
        }
        insert(queue,currNode);
    }
    return queue;
}

void shortsPath_cmd(){

}

void TSP_cmd(){

}

char getValidChar(){
    char c;
    do{
        scanf("%c",&c);
    }while (c == ' ');
    return c;
}