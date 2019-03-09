#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


#define AND -1
#define IMPLIES -2
#define NOT -3
#define OR -4


/*functions are arranged alphabatically by their name*/

int actual_elements(vector<int>* v);
bool is_small_vpointer(vector<int>* a, vector<int>* b);
void horn_algorithm(vector<vector<int>*> implications, vector<vector<int>*> pure_negations, int n);
string make_readable(int i);
pair<vector<int>*, int> process_line(string line);