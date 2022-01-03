#include "graph.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// Function to Create A New Node
List listCreateNode(pnode nodeData){

    List temp = (List)malloc(sizeof(ListHead));
    temp->nodeData = nodeData;
    temp->next = NULL;
    temp->prev = NULL;
	temp->tail = NULL;
    return temp;
}
 
// Return the value at head
List listPeek(List head,int id){
	// printf("zdfbzsfbzdfb\n");
	// fflush(NULL);
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
	// printf("Trying to remove %p,%d",head,id);
	// fflush(NULL);
	List currNode = head;
	// printf("got here\n");
	// fflush(NULL);	
    while (currNode != NULL){
		// printf("got here 0\n");
    	// fflush(NULL);
		if (currNode->nodeData->node_num == id){
			// printf("got here 0.1\n");
    		// fflush(NULL);
			// If true it mean currNode is head.
			if (currNode->prev == NULL){
				// printf("got here 0.2\n");
    			// fflush(NULL);
				head = head->next;
				// printf("got here 0.3\n");
    			// fflush(NULL);
				if (head != NULL){
					head->prev = NULL;
				}
				// printf("got here 0.4\n");
    			// fflush(NULL);
				free(currNode);
				// printf("got here1\n");
    			// fflush(NULL);
			}
		}
		// printf("got here4\n");
    	// fflush(NULL);
		currNode = currNode->next;
	}
	// printf("finise the remove func\n");
	// fflush(NULL);
    return head;
}
 
// Function to push according to priority
List listInsert(List head, pnode nodeData){
    // printf("im in with %d\n",nodeData->node_num);
    // fflush(NULL);
	// Create new Node
    List temp = listCreateNode(nodeData);
	// printf("got here1\n");
    // fflush(NULL);
    if(head != NULL){
		temp->next = head;
		head->prev = temp;
		head = temp;
		// printf("got here2\n");
    	// fflush(NULL);
    }
	else{
    	head = temp;
		head->tail = temp;
		// printf("got here2\n");
    	// fflush(NULL);
	}
	// printf("got here3\n");
    // fflush(NULL);
    // printf("%p,%d\n",temp,temp->nodeData->node_num);
    // fflush(NULL);
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