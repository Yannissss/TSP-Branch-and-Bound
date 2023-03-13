#ifndef GRAPH_H
#define GRAPH_H

// Structure contenant les données d'un graphe
typedef struct {
    int vertices;    // Nombre de sommets
    int* raw_matrix; // Matrice d'ajdacence
    int** weights;   // Matrice de poids manipulable
} graph_t;

// Structure contenant les informations d'une arête
typedef struct {
    int u, v, weight;
} edge_t;

// Lit un graphe depuis un fichier
void graph_read(graph_t* graph, char* filepath);

// Détruit un graphe
void graph_drop(graph_t* graph);

// Affiche un graphe
void graph_show(graph_t* graph);

// Renvoie toutes les arếtes du graphe triées par ordre croissant
edge_t* graph_sorted_edges(graph_t* graph);

// Calcul l'arbre recouvrant de poids minimal du graphe en utilisant
// l'algorithme de Kruskal
// `tree` doit pouboir contenir exactement (n - 1) arêtes
// Aucun test n'est fait dans cette fonction
int graph_minimum_spanning_tree(graph_t* graph, edge_t* tree);

#endif /* GRAPH_H */
