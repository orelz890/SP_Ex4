#include "graph.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// Function to Create A New Node
List listCreateNode(pnode nodeData){

    List temp = (List)malloc(sizeof(ListHead));
	if (temp == NULL){
		return NULL;
	}
    temp->nodeData = nodeData;
    temp->next = NULL;
    temp->prev = NULL;
	temp->tail = NULL;
    return temp;
}
 
// Return the value at head
List listPeek(List head,int id){
	List ans = head;
	while (ans != NULL && ans->nodeData->node_num != id){
		ans = ans->next;
	}
	if(ans == NULL){
		return NULL;
	}
    return ans;
}
 
List listRemove(List head, int id){
	List currNode = head;	
    while (currNode != NULL){
		List nextOne = currNode->next;
		if (currNode->nodeData->node_num == id){
			// If true it mean currNode is head.
			if (currNode->prev == NULL){
				head = head->next;
				if (head != NULL){
					head->prev = NULL;
				}
				free(currNode);
			}
		}
		currNode = nextOne;
	}
    return head;
}
 
// Function to push according to priority
List listInsert(List head, pnode nodeData){
	// Create new Node
    List temp = listCreateNode(nodeData);
    if(head != NULL){
		temp->next = head;
		head->prev = temp;
		head = temp;
    }
	else{
    	head = temp;
		head->tail = temp;
	}
    return head;
}

int listIsEmpty(List head){
	printf("sbdfbadf\n");
	fflush(NULL);
    return head == NULL;
}
List list_clone(List head) {
	List copy= NULL;
	List old= head;
	while (old != NULL){
		listInsert(copy,old->nodeData);
		old = old->next;
	}
	return copy;
}