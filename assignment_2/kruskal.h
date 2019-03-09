/*fucntions are arranged in alphabatic order of function return types*/

#include <vector>
using namespace std;
struct edge {
	int n1;
	int n2;
	int weight;
};



struct neigh {
	int name;
	int weight;
};


struct node {
	int name;
	vector<edge*> edges;
	int visited;
	node* prev;
};

bool IsSmallEdge (edge* a, edge* b);
pair<vector<edge* >, vector<edge* > > minimum_spanning_tree(node** nodes, vector<edge*> edges, int n);