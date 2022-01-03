#include <math.h>
#include <limits.h>
#include <string.h>
#include "graph.h"
#include "priorityQueue.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

#define NOPATH 1
#define WORKED 0

PriorityQ setAllTags(PriorityQ queue,int src);

static pnode head;

char build_graph_cmd(){
    if (head != NULL){
        deleteGraph_cmd();
        printGraph_cmd();
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
        existingNode->edges = NULL;
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
            // fflush(NULL);
        }
    } while ((first - '0') >= 0 && (first - '0') <= 9);
    // printf("finished and first = %c\n",first);
    // fflush(NULL);
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
    return currNode;
}

void delete_node_cmd(){
    char c;
    c = getValidChar();
    int id = c - '0';
    removeNode(id);
}

int removeNode(int id){
    // printf("node id is: %d\n",id);
    // fflush(NULL);
    pnode currentNode = findNode(id);
    if (id < 0 || currentNode == NULL){
        return -1;
    }
    
    // Erasing all the edges that there dest is this node.
    pnode nodeToRemove = NULL;
    pnode tempNode = head;
    // printf("head node: %d\n",head->node_num);
    // fflush(NULL);
    while (tempNode != NULL){
        if (tempNode->node_num != id){
            // printf("currNode is : %d\n",tempNode->node_num);
            // fflush(NULL);
            pedge tempEdge = tempNode->edges;
            pedge prevEdge = NULL;
            while (tempEdge != NULL){
                // printf("currEdge is : (%d,%d)\n",tempNode->node_num,tempEdge->endpoint->node_num);
                // fflush(NULL);
                pedge nextEdge = tempEdge->next;
                if (tempEdge->endpoint->node_num == id){
                    // printf("currEdge removed : (%d,%d)\n",tempNode->node_num,tempEdge->endpoint->node_num);
                    // fflush(NULL);
                    if (prevEdge != NULL){
                        prevEdge->next = nextEdge;
                    }else{
                        tempNode->edges = nextEdge;
                    }
                    free(tempEdge);
                    tempNode->edgeSize -= 1;
                }
                else{
                    prevEdge = tempEdge;
                }
                tempEdge = nextEdge;
                // Now temp edge is NULL therefore, prevEdge is the tail.
                tempNode->tail = prevEdge;
            }
        }else{
            nodeToRemove = tempNode;
            // printf("im1\n");
            // fflush(NULL);
        }
        // printf("finished a node iteration\n");
        // fflush(NULL);
        tempNode = tempNode->next;
    }
        // printf("im3\n");
        // fflush(NULL);
        // Erasing this node edges and itself.
        pedge tempEdge = nodeToRemove->edges;
        while (tempEdge != NULL){
            pedge nextEdge = tempEdge->next;
            free(tempEdge);
            tempEdge = nextEdge;
        }
        if (nodeToRemove->prev != NULL){
            nodeToRemove->prev->next = nodeToRemove->next;
        }
        if (nodeToRemove->next != NULL){
            nodeToRemove->next->prev = nodeToRemove->prev;
        }
        free(nodeToRemove);
    
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
    while (head != NULL){
        pnode next = head->next;
        removeNode(head->node_num);
        head = next;
    }
    
    // pnode tempNode = head;
    // while (tempNode != NULL){
    //     printf("%p, current node to delete: %d\n",tempNode,tempNode->node_num);
    //     fflush(NULL);
    //     pedge currEdge = tempNode->edges;
    //     while (currEdge != NULL){
    //         printf("current edge deleted (%d,%d)\n",tempNode->node_num,currEdge->endpoint->node_num);
    //         fflush(NULL);
    //         pedge nextEdge = currEdge->next;
    //         free(currEdge);
    //         tempNode->edgeSize -= 1;
    //         currEdge = nextEdge;
    //     }
    //     tempNode = tempNode->next;
    // }
    // printf("cosemak va cosemak %d,%d,%d",head->node_num,head->weight,head->edgeSize);
    // pnode firstNode = head;
    // while (firstNode != NULL){
    //     printf("%p,%d\n",tempNode,tempNode->node_num);
    //     fflush(NULL);
    //     pnode nextNodeInLine = tempNode->next;
    //     free(tempNode);
    //     tempNode = nextNodeInLine;
    // }
}

int dijkstra(int src){
    // printf("im1");
    // fflush(NULL);
    PriorityQ queue = NULL;
    queue = setAllTags(queue,src);
    // printf("im2");
    // fflush(NULL);

    if(queue == NULL){
        return INT_MAX;
    }
    // printf("im3");
    // fflush(NULL);
    while (isEmpty(queue) != 1){

        PriorityQ peeking = peek(queue);
        pnode temp_node = peeking->nodeData;
        queue = delete(queue,peeking);
        pedge currEdge = temp_node->edges;
        while (currEdge != NULL){
            int new_weight = temp_node->weight + currEdge->weight;
            if (temp_node->weight == INT_MAX){
                new_weight = INT_MAX;
            }
            if (new_weight < currEdge->endpoint->weight){
                // if (currEdge->endpoint->node_num == 3){
                    // printf("%d,(edge (%d,%d),temp node %d) == (%d+%d)"
                //         ,currEdge->endpoint->weight,temp_node->node_num,currEdge->endpoint->node_num,
                //         temp_node->node_num,currEdge->weight,temp_node->weight);
                //     fflush(NULL);
                // }
                currEdge->endpoint->weight = new_weight;
                currEdge->endpoint->perent = temp_node;
            }
            // printf("currEdge == (%d,%d)\n",temp_node->node_num,currEdge->endpoint->node_num);
            // fflush(NULL);
            currEdge = currEdge->next;
        }
    }
    // printf("im4");
    // fflush(NULL);

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

int shortsPath_cmd(int src, int dest){

    pnode destNode = findNode(dest);
    pnode srcNode = findNode(src);
    // printf("(%d,%d) src = %d, dest = %d\n",srcNode->weight,destNode->weight,src,dest);
    // fflush(NULL);
    if (srcNode== NULL || destNode == NULL){
        printf("One of the input dont exist! try again..\n");
        return INT_MAX;
    }
    dijkstra(src);
    return destNode->weight;
}

int TSP_cmd(int num){
    // printf("starting TSP\n");
    // fflush(NULL);
    if (num == 0){
        return 0;
    }
    int cities[num];
    for (size_t i = 0; i < num; i++){
        char c = getValidChar();
        cities[i] = c - '0';
        // printf("%c\n",c);
        // fflush(NULL);
    }
    if (num == 1){
        return 0;
    }
    // printf("im1\n");
    // fflush(NULL);
    int shorts_path_of_all = INT_MAX;
    for (int i = 0; i < num; i++){
        List Lhead = NULL;
        int listSize = num;
        int current_shortest_path = INT_MAX;
        for (int j = 0; j < num; j++){
            if (i != j){
                Lhead = listInsert(Lhead, findNode(cities[j]));
                // printf("%d added to the list!\n",Lhead->nodeData->node_num);
            }
        }
        Lhead = listInsert(Lhead, findNode(cities[i]));

        pnode currNode = Lhead->nodeData;
        // printf("currNode = %d\n", currNode->node_num);
        // fflush(NULL);
        Lhead = listRemove(Lhead,cities[0]);
        listSize -= 1;
        // printf("im3\n");
        // fflush(NULL);

        int ans = 0;
        while (listSize > 0){
            // printf("hey\n");
            // fflush(NULL);
            List src = NULL;
            int shortest_dist = INT_MAX;
            // printf("list size is: %d\n",listSize);
            // fflush(NULL);
            List tempHead = NULL;
            tempHead = Lhead;
            // printf("pointer = %p val %d , pointer2 = %p\n",Lhead,Lhead->nodeData->node_num,tempHead);
            // fflush(NULL);
            while(tempHead != NULL){
                // printf("the current city: %d and the current node %d\n",tempHead->nodeData->node_num,currNode->node_num);
                // fflush(NULL);
                int dist = shortsPath_cmd(currNode->node_num,tempHead->nodeData->node_num);
                // printf("the dist is : %d\n",dist);
                // fflush(NULL);
                if (dist < shortest_dist && tempHead->nodeData->node_num != currNode->node_num){
                    src = tempHead;
                    shortest_dist = dist;
                    // printf("the shortest_dist is: %d between %d and %d\n",shortest_dist,currNode->node_num,tempHead->nodeData->node_num);
                    // fflush(NULL);
                }
                tempHead = tempHead->next;
                // printf("pointer = %p , pointer2 = %p\n",Lhead,tempHead);
                // fflush(NULL);
            }
            // printf("sfbafb %p\n",src);
            // fflush(NULL);
            if(src != NULL){
                currNode = listPeek(Lhead,src->nodeData->node_num)->nodeData;
            }
            else{
                ans = INT_MAX;
                break;
            }
            // printf("currNode = %d\n",currNode->node_num);
            // fflush(NULL);
            Lhead = listRemove(Lhead,src->nodeData->node_num);
            // printf("pointer = %p , val = %d\n",Lhead,Lhead->nodeData->node_num);
            // fflush(NULL);
            listSize -= 1;
            // printf("im5\n");
            // fflush(NULL);
            if (shortest_dist == INT_MAX){
                ans = INT_MAX;
            }
            else{
                ans += shortest_dist;
            }
        }
        current_shortest_path = ans;
        if (shorts_path_of_all > current_shortest_path){
            shorts_path_of_all = current_shortest_path;
        }
        // printf("current ans == %d\n",ans);
        // printf("current shortest path of all== %d\n",shorts_path_of_all);
        // fflush(NULL);        
    }
    if (shorts_path_of_all == INT_MAX){
        return -1;
    }
    
    return shorts_path_of_all;
}

char getValidChar(){
    char c;
    do{
        scanf("%c",&c);
    }while (c == ' ');
    return c;
}