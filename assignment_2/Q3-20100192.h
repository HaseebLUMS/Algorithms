struct node {
	int index;
	int constraint;
};
void game(int n, node* col_constraints, node* row_constraints);
bool isGreater(node a, node b);