#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;



struct plane_st {
	int id;
	int tries;
};
struct invalid {
	int plane;
	int port;
};

struct port_st {
	int id;
	plane_st accomodated_plane;
};

void fileReading(int& n, int** &planePreferences, int** &portPreferences, vector<invalid>& X);
void GaleShapley(int n, int** &planePreferences, int** &portPreferences, vector<invalid> X);
bool is_compatible(int plane, int port, vector<invalid> X);
bool is_prefered_over_old(int current, int old, int* portPrefs, int n);