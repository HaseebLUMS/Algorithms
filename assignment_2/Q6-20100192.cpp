#include "Q6-20100192.h"

			/*
			 * I have used the algorithm from a course site
			 * of Stanford. The algorithm provided gives l-
			 * inear time complexity. Screenshot of the al-
			 * gorithm is provided with the assignment sub-
			 * mission.*/


int main() {
	vector<vector<int>*> implications;/*vector of vector x pointers where x are vectors containing impications equations*/
	vector<vector<int>*> pure_negations; /*vector of vector x pointers where x are vectors containing pure negations*/

	fstream file;
	string fn = "0"; cout << "file=> ";
	cin >> fn;
	file.open(fn.c_str());cout << endl;
	string line;
	getline(file, line);
	int n = stoi(line . substr(2));
	while(getline(file, line)) {
		pair<vector<int>*, int> p; /*second int == 0 => implications | == 1 => pure_negations*/
		p = process_line(line);
		if(p.second) {pure_negations.push_back(p.first);}
		else {implications.push_back(p.first);}
	}

	horn_algorithm(implications, pure_negations, n);
	return 0;
}



pair<vector<int>*, int> process_line(string line) {
	int break_point = 0;
	vector<int> * vec = new vector<int>;
	int f = 0;
	for(int i = 0; i< line.length(); i++) {

		if(isdigit(line[i])) {vec -> push_back(stoi(line.substr(i,1)));}
		else if (line[i] == '^') {vec -> push_back(AND);}
		else if (line[i] == 'v') {vec -> push_back(OR);}
		else if (line[i] == '\'') {vec -> push_back(NOT); f = 1;}
		else if (line[i] == '>') {vec -> push_back(IMPLIES);}
	}

	return make_pair(vec, f);
}



string make_readable(int i) {
	if(i == AND) {return " AND ";}
	if(i == IMPLIES) {return " => ";}
	if(i == NOT) {return "\' ";}
	if(i == OR) {return " OR ";}
	else {return to_string(i);}
}


bool is_small_vpointer(vector<int>* a, vector<int>* b) {
	return (a -> size() < b -> size()) ? true : false;
}


int actual_elements(vector<int>* v) {
	int ans = 0;
	for (int i = 0; i< v -> size(); i++) {
		if ((*v)[i] > -1) {
			ans++;
		}
	}
	return ans;
}

void horn_algorithm(vector<vector<int>*> implications, vector<vector<int>*> pure_negations, int n) {
	sort(implications.begin(), implications.end(), is_small_vpointer);

	vector<int> true_variables;
	for(int i = 0; i < implications.size(); i++) {
		vector<int>* v = implications[i];
		if(actual_elements(v) == 1) {
			/*It is => x i.e (-2,X)*/
			int tv = (*v)[v->size() - 1];
			true_variables.push_back(tv);
			/*removing the true variable from all vectors in implications*/
			for(int k = 0; k < implications.size(); k++) {
				vector<int> * u = implications[k];
				vector<int>::iterator iter = u -> begin();
				vector<int>::iterator iter2 = u -> begin();
				for(iter = u -> begin(); iter != (u -> end())-2; iter ++) {
					iter2++;
					if (*iter == tv) {
						break;
					}
				}
				if(iter != (u -> end())-2) {u -> erase(iter);}
			}
		}
	}



	//cout << "Trues" << endl;
	int* T = new int[n+1];
	for(int i = 0; i< true_variables.size(); i++) {
		T[true_variables[i]] = 1;
		//cout << "x" << true_variables[i] << " : " << "1" << endl;
	}cout << endl;

	for(int i = 1; i< n+1; i++) {
		cout << "x" << i << " :" << T[i] << endl;
	}
	cout << endl;

	/*At this point, I have all the variable set to 0 or 1 correctly in arr T*/
	/*checking pure negations against variables*/

	int out = 1;
	for(int i = 0; i< pure_negations.size(); i++) {
		vector<int> * v = pure_negations[i];
		int ans = 1;

		vector<int> w;

		for(int j = 0; j < v -> size(); j++) {
			if((*v)[j] == NOT) {
				w[w.size()-1] = !(w[w.size()-1]);
			}
			else if((*v)[j] > 0){
				w.push_back(T[(*v)[j]]);
			}
			else {w.push_back((*v)[j]);}
		}


		//for(int j = 0; j< w.size(); j++) {cout << w[j] << " ";}cout << endl;

		int s = 0;
		while(s < w.size()) {
			if(w[s] == AND) {
				if(w[s-1] == 0 || w[s+1] == 0) {
					ans = 0;
					w[s+1] = 0;
				}
				else {
					ans = 1;
					w[s+1] = 1;
				}
			}
			if(w[s] == OR) {
				//cout << w[s] << " " << w[s-1] << " " << w[s+1] << endl;
				if(w[s-1] == 1 || w[s+1] == 1) {
					ans = 1;
					w[s+1] = 1;
				}
				else {
					w[s+1] = 0;
					ans = 0;
				}
			}
			s++;
			//cout << ans << endl;
		}
		

		if(ans == 0) {out = 0; break;}

	}

	if(!out) {cout << "Not Satisfiable." << endl;}
	else {cout << "Satisfiable" << endl;}
}
