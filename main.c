#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "graph.h"

int char_ditecter(char c);

int main(){
    char c;
    do{
        c = getValidChar();
        char_ditecter(c);
    } while (c != '\n');
    deleteGraph_cmd();
    return 0;
}

int char_ditecter(char c){
    char ans;
    // Add node.
    if(c == 'B' || c == 'n'){
        ans = insert_node_cmd();
        char_ditecter(ans);
    }
    // Create a new graph.
    if((c == 'A')){
        ans = build_graph_cmd();
        char_ditecter(ans);
    }
    // Delete node (and relevate edges).
    if(c == 'D'){
        delete_node_cmd();
    }
    // Calculates the shortest path between src and dest.
    if (c == 'S'){
        shortsPath_cmd();
    }
    // Given a list of node it calculates the shortest path that goes through them all. 
    if (c == 'T'){
        TSP_cmd();
    }
    if (c == 'P'){
        printGraph_cmd();
    }
    
    return 0;
}
