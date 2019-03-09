/*functions arranged alphabetically on the basis of return type*/
struct pr_struct {
	double pr;
	int L;
	double p;
	int i;
};


bool on_pr(pr_struct a, pr_struct b);
double expectation(pr_struct* Lp, int n);
int give_index(int* L, int value, int n);
void give_arrangement(int* L, int n, double* p);