#ifndef GRAPH_H
#define GRAPH_H

// Structure contenant les données d'un graphe
typedef struct {
    int vertices;    // Nombre de sommets
    int* raw_matrix; // Matrice d'ajdacence
    int** weights;   // Matrice de poids manipulable
} graph_t;

// Lit un graphe depuis un fichier
void graph_read(graph_t* graph, char* filepath);

// Détruit un graphe
void graph_drop(graph_t* graph);

// Affiche un graphe
void graph_show(graph_t* graph);

#endif /* GRAPH_H */
