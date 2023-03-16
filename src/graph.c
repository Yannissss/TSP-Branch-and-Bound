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

void print_vecedge(edge_t* v, int len) {
    printf("[");
    for (int i = 0; i < len - 1; i++) {
        edge_t e = v[i];
        printf("(%d, %d, %d), ", e.u, e.v, e.weight);
    }
    edge_t e = v[len - 1];
    printf("(%d, %d, %d)]", e.u, e.v, e.weight);
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
            graph->weights[i][i] = 0;
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

int cmp_edge(const void* a, const void* b) {
    edge_t* lhs = (edge_t*)a;
    edge_t* rhs = (edge_t*)b;
    if (lhs->weight < rhs->weight) {
        return -1;
    } else if (lhs->weight == rhs->weight) {
        return 0;
    } else {
        return 1;
    }
}

edge_t* graph_sorted_edges(graph_t* graph) {
    int vertices = graph->vertices;
    int num_edges = vertices * (vertices - 1) / 2;
    edge_t* edges = (edge_t*)malloc(sizeof(edge_t) * num_edges);

    int i = 0;
    for (int u = 0; u < vertices; u++) {
        for (int v = u + 1; v < vertices; v++) {
            edges[i].u = u;
            edges[i].v = v;
            edges[i].weight = graph->weights[u][v];
            i++;
        }
    }

    // Tri des arếtes
    qsort((void*)edges, num_edges, sizeof(edge_t), cmp_edge);

    return edges;
}

// Renvoie le représentant d'un élément dans une structure Union-Find
int uf_find(int* uf, int x) {
    int next = uf[x];
    if (next != x) {
        uf[x] = uf_find(uf, next);
    }
    return uf[x];
}

void graph_minimum_spanning_tree(graph_t* graph, tree_t* tree) {
    int vertices = graph->vertices;

    // Composantes connexes
    int* components = (int*)malloc(sizeof(int) * vertices);
    for (int u = 0; u < vertices; u++)
        components[u] = u;

    // Arêtes triées
    int num_edges = vertices * (vertices - 1) / 2;
    edge_t* edges = graph_sorted_edges(graph);

    // Algorithme Kruskal
    int weight = 0;
    edge_t* edge = &edges[0];
    edge_t* end = edges + num_edges;
    for (int i = 0; i < vertices - 1; i++) {
        while (edge < end) {
            int u = edge->u;
            int v = edge->v;

            int u_root = uf_find(components, u);
            int v_root = uf_find(components, v);

            if (u_root != v_root) {
                components[u_root] = v_root;
                edge++;
                break;
            }

            edge++;
        }

        if (edge < end) {
            tree->edges[i] = *edge;
            weight += edge->weight;
        }
    }

    tree->weight = weight;

    free(components);
    free(edges);
}

void tree_new(tree_t* tree, graph_t* graph) {
    tree->weight = 0;
    tree->num_edges = graph->vertices - 1;
    tree->edges = (edge_t*)malloc(sizeof(edge_t) * (graph->vertices - 1));
}

void tree_drop(tree_t* tree) { free(tree->edges); }

void tree_show(tree_t* tree) {
    printf("tree_t {\n");
    printf("    weight: %d, \n", tree->weight);
    printf("    edges: ");
    print_vecedge(tree->edges, tree->num_edges);
    printf("\n}\n");
}
