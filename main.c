
#include <stdio.h>
#include <string.h>
#include "graph.h"

int char_ditecter(char c);

char c;
do{
    scanf("%c",&c);
    char_ditecter(c);
} while ((c != '\t' && c != '\n');

int char_ditecter(char c){
    char ans;
    // Add node.
    if(c == 'B' || c == 'n'){
        ans = insert_node_cmd(pnode);
        if (ans != NULL){
            char_ditecter(ans);
        }
    }
    // Create a new graph.
    if((c == 'A')){
        ans = build_graph_cmd(pnode);
        if (ans != NULL){
            char_ditecter(ans);
        }
    }
    // Delete node (and relevate edges).
    if(c == 'D'){
        ans = delete_node_cmd(pnode);
    }
    // Calculates the shortest path between src and dest.
    if (c == 'S'){
        ans = shortsPath_cmd(*pnode);
    }
    // Given a list of node it calculates the shortest path that goes through them all. 
    if (c == 'T'){
        ans = TSP_cmd(*pnode);
    }
    if (c == '\n'){
        ans = deleteGraph_cmd(*pnode);
    }
    return 0;
}