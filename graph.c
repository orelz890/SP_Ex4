#include <math.h>
#include <limits.h>
#include <string.h>
#include "graph.h"
#include "priorityQueue.h"
#include <stdio.h>
#include <stdlib.h>

#define NOPATH 1
#define WORKED 0

PriorityQ setAllTags(PriorityQ queue,int src);

static pnode head;

char build_graph_cmd(){
    if (head != NULL){
        deleteGraph_cmd();
    }
    char c = getValidChar();
    int nodesNum = c - '0';
    for (size_t i = 0; i < nodesNum; i++){
        pnode currNode = NULL;
        currNode = (pnode) malloc(sizeof(node)); // need to free!!!
        addNode(currNode,i);
    }
    char currChar = getValidChar();
    while (currChar == 'n'){
        char currNode = getValidChar();
        pnode temp = findNode(currNode - '0');
        currChar = creatAllGivenEdges(temp);
    }
    return currChar; 
}

char insert_node_cmd(){
    char c = getValidChar();
    int id = c -'0';
    pnode existingNode = findNode(id);
    // if (existingNode != NULL){
    //     printf("%d\n",existingNode->node_num);
    // }
    // fflush(NULL);
    if (existingNode != NULL){
        pedge currEdge = existingNode->edges;
        while (existingNode->edgeSize != 0){
            pedge nextEdge = currEdge->next;
            // printf("before = %d\n", currEdge->weight);
            // fflush(NULL);
            free(currEdge);
            existingNode->edgeSize -= 1;
            // printf("after = %d\n", currEdge->weight);
            // fflush(NULL);
            currEdge = nextEdge;
            // printf("next = %d\n", currEdge->weight);
        }      
    }
    else{
        pnode currNode = (pnode) malloc(sizeof(node)); // need to free!!!
        existingNode = addNode(currNode,id);
    }
    // printf("%p,%d\n",existingNode->edges,existingNode->node_num);
    // fflush(NULL);
    char ans = creatAllGivenEdges(existingNode);
    return ans;
}

char creatAllGivenEdges(pnode existingNode){

    char first;
    char sec;
    do{
        first = getValidChar();
        int dest = first - '0';
        if (dest >= 0 && dest <= 9){
            sec = getValidChar();
            int weight = sec - '0';
            addEdge(existingNode,dest,weight);
            // printf("dest = %d, weight = %d\n",dest,weight);
            fflush(NULL);
        }
    } while ((first - '0') >= 0 && (first - '0') <= 9);
    // printf("finished and first = %c\n",first);
    fflush(NULL);
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
    int i = 0;
    while (edgesPointer != NULL && i < currNode->edgeSize){
        if ((edgesPointer->endpoint)->node_num == dest){
            return edgesPointer;
        }
        i+=1;
        // printf("im here: %p,%d\n",edgesPointer,edgesPointer->endpoint->node_num);
        // fflush(NULL);
        edgesPointer = edgesPointer->next;
    }
    return NULL;
}

void addEdge(pnode node, int dest, int weight){
    // printf("%p,%d,%d",node,dest,weight);
    // fflush(NULL);
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
            node->tail = newEdge;
        }
        else{
            newEdge->next = node->edges;
            node->edges = newEdge;
        }
        node->edgeSize += 1;
    }
}

pnode addNode(pnode currNode,int id){
    currNode->node_num = id;
    currNode->edges = NULL;
    currNode->tail = NULL;
    currNode->next = NULL;
    currNode->prev = NULL;
    currNode->perent = NULL;
    currNode->weight = INT_MAX;
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
        if (tempNode->node_num != id){
            tempNode->next = currNode;
            currNode->prev = tempNode;
        }
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
        fflush(NULL);
        int i = 0;
        pedge currEdge = currNode->edges;
        while (currEdge != NULL && i < currNode->edgeSize){
            printf("(%d,%d), ",currEdge->endpoint->node_num, currEdge->weight);   
            fflush(NULL);
            i+=1;
            currEdge = currEdge->next;
        }
        printf("}\n");
        fflush(NULL);
        currNode = currNode->next;
    }
}

void deleteGraph_cmd(){
    // Erasing all the edges to this node
    pnode tempNode = head;
    while (tempNode != NULL){
        // printf("%p,%d\n",tempNode,tempNode->node_num);
        // fflush(NULL);
        pedge currEdge = tempNode->edges;
        while (currEdge != NULL && currEdge->weight > 0){
            // printf("%d,%d\n",currEdge->endpoint->node_num,currEdge->weight);
            // fflush(NULL);
            pedge nextEdge = currEdge->next;
            free(currEdge);
            tempNode->edgeSize -= 1;
            currEdge = nextEdge;
        }
        free(tempNode);
        tempNode = tempNode->next;
    }
    // printf("cosemak va cosemak %d,%d,%d",head->node_num,head->weight,head->edgeSize);
    // // pnode firstNode = head;
    // // while (firstNode != NULL){
    // //     printf("%p,%d\n",tempNode,tempNode->node_num);
    // //     fflush(NULL);
    // //     pnode nextNodeInLine = tempNode->next;
    // //     free(tempNode);
    // //     tempNode = nextNodeInLine;
    // // }
}

int dijkstra(int src){
    PriorityQ queue = NULL;
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

PriorityQ setAllTags(PriorityQ queue,int src){
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
        // printf("id: %d\n",currNode->node_num);
        // fflush(NULL);
        queue = insert(queue,currNode);
        currNode = currNode->next;
    }
    return queue;
}

float shortsPath_cmd(int src, int dest){
    dijkstra(src);
    // pnode destNode = findNode(dest);
    // pnode srcNode = findNode(src);
    // float sum = 0;
    // if(src == dest){
    //     return 0;
    // }
    // if (srcNode== NULL || destNode == NULL){
    //     printf("-1");
    //     return -1;
    // }
    // while (destNode->perent->node_num != src){
    //     pedge edge = findEdge(destNode, destNode->perent->node_num);
    //     sum = sum + edge->weight;
    //     destNode = destNode->perent;
    // }
    // if (sum == INT_MAX){
    //     printf("-1");
    //     return -1;
    // }
    // return sum;
    return 0.0;
}

float TSP_cmd(int num){
    int temp;
    int lopps = num;
    int minPath =  INT_MAX;
    int cities[num];
    int n;
    for (int i = 0; i < num; i++) {
        n = getValidChar() - '0';
        cities[i] = n;
    }
    for (int j = 0; j <num; j++){
        for (int i = 0; i < num-j; i++) {
            // if size is odd, swap 0th i.e (first) and
            // (size-1)th i.e (last) element
            if ((num-j) % 2 == 1){
                temp = cities[0];
                cities[0]=cities[num-j - 1];
                cities[num-j - 1] = temp;}
            
                // If size is even, swap ith and
                // (size-1)th i.e (last) element
            else if((num-j) % 2 == 0){
                temp =cities[i];
                cities[i]=cities[num-j - 1];
                cities[num-j - 1] = temp;
                }
        }
    if ((num-j) == 1) {
            int sum = 0;
            for (int j = 0; j < lopps-1; ++j) {
                sum += shortsPath_cmd(cities[j], cities[j + 1]);
            }
            if (sum < minPath) {
                minPath = sum;
            }
        }
        }
    if(minPath == INT_MAX){
        minPath = -1;
    }
    return minPath;
}

char getValidChar(){
    char c;
    do{
        scanf("%c",&c);
    }while (c == ' ');
    return c;
}