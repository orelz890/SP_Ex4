#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "graph.h"

char char_ditecter(char c);

int main(){
    char c;
    do{
        c = getValidChar();
        // printf("returns %c\n",c);
        char_ditecter(c);
    } while (c != '\n');
    // printf("finished");
    deleteGraph_cmd();
    return 0;
}

char char_ditecter(char c){
    // printf("current char is: %c\n",c);
    char ans = ' ';
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
        char src = getValidChar();
        char dest = getValidChar();
        int answer = shortsPath_cmd(src-'0',dest-'0');
        printf("Dijsktra shortest path: %d \n", answer);
    }
    // Given a list of node it calculates the shortest path that goes through them all. 
    if (c == 'T'){
        char s = getValidChar();
        int answer = TSP_cmd(s - '0');
        printf("TSP shortest path: %d \n", answer);
    }
    if (c == 'P'){
        printGraph_cmd();
    }
    // printf("next in line is %c\n",ans);
    return ans;
}
