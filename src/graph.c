#include "graph.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_veci(int* v, int len) {
    printf("[");
    for (int i = 0; i < len - 1; i++) {
        if (v[i] < INT_MAX)
            printf("%3d, ", v[i]);
        else
            printf("inf, ");
    }
    if (v[len - 1] < INT_MAX)
        printf("%3d]", v[len - 1]);
    else
        printf("inf]");
}
void graph_read(graph_t* graph, char* filepath) {
    char str_tmp[128];
    FILE* file;

    if ((file = fopen(filepath, "r"))) {
        int vertices;

        // Lecture du nombre de sommets
        fscanf(file, "%s", str_tmp);
        fscanf(file, "%d", &vertices);

        // Allocation mémoire
        graph->vertices = vertices;
        graph->raw_matrix = (int*)malloc(sizeof(int) * vertices * vertices);
        graph->weights = (int**)malloc(sizeof(int*) * vertices * vertices);
        for (int i = 0; i < vertices; i++)
            graph->weights[i] = &graph->raw_matrix[i * vertices];

        // Remplissage des poids à l'infini
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                graph->weights[i][j] = INT_MAX;
            }
        }

        // Lecture des caractéristiques
        int tmp;
        fscanf(file, "%s", str_tmp);
        fscanf(file, "%d", &tmp);
        if (tmp != 0) {
            fprintf(file, "Graphe orienté non supporté!\n");
        }

        fscanf(file, "%s", str_tmp);
        fscanf(file, "%d", &tmp);
        if (tmp != 1) {
            fprintf(file, "Graphe non valué non supporté!\n");
        }

        // Lecture des arếtes
        fscanf(file, "%s", str_tmp);
        fscanf(file, "%s", str_tmp);
        while (strcmp(str_tmp, "FIN_DEF_ARETES") != 0) {
            int u, v, w;

            u = atoi(str_tmp);
            fscanf(file, "%d", &v);
            fscanf(file, "%d", &w);

            graph->weights[u][v] = w;
            graph->weights[v][u] = w;

            fscanf(file, "%s", str_tmp);
        }
    } else {
        fprintf(stderr, "Lecture du fichier \"%s\" impossible \n", filepath);
    }
}

void graph_drop(graph_t* graph) {
    free(graph->weights);
    free(graph->raw_matrix);
}

void graph_show(graph_t* graph) {
    int vertices = graph->vertices;

    printf("graph_t {\n");
    printf("    vertices: %d, \n", vertices);
    printf("    weights: [\n");
    for (int i = 0; i < vertices; i++) {
        printf("        ");
        print_veci(graph->weights[i], vertices);
        printf(", \n");
    }
    printf("    ]\n");
    printf("}\n");
}
