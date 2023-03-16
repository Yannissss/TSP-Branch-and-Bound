#ifndef __GRAPH_H__
#define __GRAPH_H__

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

// Structure contenant un arbre recouvrant d'un graphe
typedef struct {
    int weight;
    int num_edges;
    edge_t* edges;
} tree_t;

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
void graph_minimum_spanning_tree(graph_t* graph, tree_t* tree);

// Alloue une structure pouvant contenir un arbre recouvrant pour un graphe
void tree_new(tree_t* tree, graph_t* graph);

// Détruit la structure contenant un arbre recouvrant
void tree_drop(tree_t* tree);

// Affiche un arbre recouvrant
void tree_show(tree_t* tree);

#endif /* __GRAPH_H__ */
