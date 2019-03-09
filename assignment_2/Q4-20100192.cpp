#include <algorithm>
#include <iostream>
#include "Q4-20100192.h"

using namespace std;
						/*
						 * I have taken the product of two variables L and p.
						 * Then I sort the vector.
						 * RUNTIME COMPLEXITY: O(NLOGN)
						 * */
int main() {
	int n = 0;
	string temp;

	cin >> temp >> n; /*n 5*/

	int* L = new int[n];
	double* p = new double[n];


	cin >> temp ; /*L*/ 
	for(int i = 0; i< n-1; i++) {
		cin >> temp;
		L[i] = stoi(temp.substr(0, temp.length()-1));
	} cin >> temp; L[n-1] = stoi(temp);


	cin >> temp ; /*p*/
	for(int i = 0; i< n-1; i++) {
		cin >> temp;
		p[i] = stod(temp.substr(0, temp.length()-1));
	} cin >> temp; p[n-1] = stod(temp);


	/*for(int i = 0; i< n; i++) {
		cout << L[i] << " " << p[i] << endl;
	}*/


	give_arrangement(L, n, p);
	return 0;
}


void give_arrangement(int* L, int n, double* p) {
	pr_struct* Lp = new pr_struct[n];
	for(int i = 0; i< n; i++) {
		Lp[i].L = L[i];
		Lp[i].i = i;
		Lp[i].p = p[i];
		Lp[i].pr = L[i] / p[i];
	}


	sort(Lp, Lp + n, &on_pr);

	double expected_time = expectation(Lp, n);
	/*printing the output*/
	for(int i = 0; i< n - 1; i++) {
		cout <<  Lp[i].i + 1 << ",";
	}cout << Lp[n-1].i + 1 << endl;
	cout << "Expected time: " << expected_time << endl;
}

int give_index(int* L, int value, int n) {
	for(int i = 0; i< n; i++) {
		if(L[i] == value){
			L[i] = -1;
			return i;
		}
	}
	cout << "issue in printing" << endl;
	return 0;
}

bool on_pr(pr_struct a, pr_struct b) {
	return a.pr < b.pr ? true : false;
}

double expectation(pr_struct* Lp, int n) {
	int sum_l = 0;
	double expected_time = 0.0;

	for(int i = 0; i< n; i++) {
		sum_l += Lp[i].L;
		expected_time += Lp[i].p * sum_l;
	}

	return expected_time;
}
