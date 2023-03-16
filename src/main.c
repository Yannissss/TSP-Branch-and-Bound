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
    tree_t min_span_tree;

    graph_read(&graph, filepath);

    printf("Graph = ");
    graph_show(&graph);

    tree_new(&min_span_tree, &graph);

    graph_minimum_spanning_tree(&graph, &min_span_tree);

    printf("Minimum spanning tree = ");
    tree_show(&min_span_tree);

    tree_drop(&min_span_tree);
    graph_drop(&graph);

    return EXIT_SUCCESS;
}