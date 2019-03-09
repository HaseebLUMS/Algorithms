#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

struct LEAVE
{
	int id;
	int name; //for index of leaves in array
};

struct node {
	int id;
	int value;


	int total_sum;
	int side_sum;
	LEAVE leave[2];
	vector<int>* vecs[2];

	node* left;
	node* right;
	//node* add_node(node* p);
};

void print_tree(node* p);
void maximum_ancestry(node* p);