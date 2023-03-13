#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

int main(int argc, char** argv) {
    char* filepath;
    int debug;

    if (argc > 1) {
        filepath = argv[1];
        if (argc > 2 && (strcmp("-d", argv[2]) == 0))
            debug = 1;
    } else {
        printf("Usage: \n");
        printf("%s [pb_file] [-d ?]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    graph_t graph;
    graph_read(&graph, filepath);

    graph_show(&graph);

    edge_t* tree = (edge_t*)malloc(sizeof(edge_t) * (graph.vertices - 1));

    graph_minimum_spanning_tree(&graph, tree);

    printf("Minimum spanning tree: ");
    for (int i = 0; i < graph.vertices - 1; i++)
        printf("(%d, %d, %d) ", tree[i].u, tree[i].v, tree[i].weight);
    printf("\n");

    free(tree);

    graph_drop(&graph);

    return EXIT_SUCCESS;
}