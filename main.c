#include <stdio.h>
#include <string.h>
#include "graph.h"

int char_ditecter(char c, pnode* myGraph);

int main(){
    pnode *myGraph = NULL;
    char c;
    do{
        scanf("%c",&c);
        char_ditecter(c, myGraph);
    } while ((c != '\t' && c != '\n'));

    return 0;
}

int char_ditecter(char c, pnode* myGraph){
    char ans;
    // Add node.
    if(c == 'B' || c == 'n'){
        ans = insert_node_cmd(myGraph);
        char_ditecter(ans,myGraph);
    }
    // Create a new graph.
    if((c == 'A')){
        ans = build_graph_cmd(myGraph);
        char_ditecter(ans,myGraph);
    }
    // Delete node (and relevate edges).
    if(c == 'D'){
        delete_node_cmd(myGraph);
    }
    // Calculates the shortest path between src and dest.
    if (c == 'S'){
        shortsPath_cmd(*myGraph);
    }
    // Given a list of node it calculates the shortest path that goes through them all. 
    if (c == 'T'){
        TSP_cmd(*myGraph);
    }
    if (c == '\n'){
        deleteGraph_cmd(myGraph);
    }
    return 0;
}