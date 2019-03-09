#include "kruskal.cpp"

edge* get_smallest_common_edge(vector<edge *>* discarded_edges, node* n1, node* n2, node** nodes, int n);
void traverse_and_set(node* n1, int* flags, int mark, node** nodes);
bool is_smaller_edge(edge* a, edge* b);