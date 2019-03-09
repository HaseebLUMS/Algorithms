#include "kruskal.cpp"

edge * give_edge_to_remove(vector<edge *>* included_edges, node* n1, node** nodes, int m);
void give_cycle(node* n1, node** nodes, int n, vector<edge *>* cycle);
bool is_greater(edge* a, edge* b);
