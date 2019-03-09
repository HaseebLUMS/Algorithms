#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct team{
	int id;
	int exacavation_number;
};

struct location {
	int id;
	int team_id;
	bool is_finalised;
};

void fileRead(string filename, int& n, int** &teamPreferences);

void modifiesGaleShapley(int n, int** &teamPreferences);

int get_team(int ID, vector<team> particapting_teams);

int get_location(int ID, vector<location> exacavation_locations);

int get_loc_by_team(int team, vector<location> exacavation_locations);




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
void GaleShapley(int n, int** &planePreferences, int** &portPreferences, vector<invalid> X);

bool is_compatible(int plane, int port, vector<invalid> X);
bool is_prefered_over_old(int current, int old, int* portPrefs, int n);