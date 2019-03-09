#include <algorithm>
#include <iostream>
#include "pqueue.cpp"
#include "Q3-20100192.h"
#include <string>
#include <vector>

using namespace std;
						/*
						 * I have made a mexheap of col constraints.
						 * Then I satisfy the row constrainrs one by
						 * one by taking col ind from maxheap.
						 * RUNTIME COMPLEXITY: O(NLOGN)*/
int game_piece = 11;

int main() {
	string temp;
	int n;
	cin >> temp >> n;
	cout << temp << " " <<n << endl;


	node row_constraints [n];
	node col_constraints [n];


	cin >> temp;
	for(int i = 0; i< n; i++) {
		cin >> row_constraints[i].constraint;
		row_constraints[i].index = i;
	}

	cin >> temp;
	for(int i = 0; i< n; i++) {
		cin >> col_constraints[i].constraint;
		col_constraints[i].index = i;
	}


	int row_sum = 0, col_sum = 0;
	for(int i = 0; i< n; i++) {
		row_sum += row_constraints[i].constraint;
		if(row_constraints[i].constraint > n) {
			cout << "Not Possible" << endl;
			return 0;
		}
	}


	for(int i=0; i< n; i++) {
		col_sum += col_constraints[i].constraint;
		if(col_constraints[i].constraint > n) {
			cout << "Not Possible" << endl;
			return 0;
		}
	}

	if(row_sum != col_sum || row_sum > n*n) {
		cout << "Not Possible" << endl;
		return 0;
	}

	game(n, col_constraints, row_constraints);
	return 0;
}


bool isGreater(node a, node b) {
	return a.constraint > b.constraint ? true : false;
}


void game(int n, node* col_constraints, node* row_constraints) {
	MinHeap<node> col_heap(n, &isGreater);
	for (int i = 0; i < n; ++i){
		col_heap.insertKey(col_constraints[i]);
	}


	int** matrix = new int*[n];
	for(int i=0; i< n; i++) {
		matrix[i] = new int[n];
	}
	vector<pair<int, int> > output;


	for(int i = 0; i< n; i++) {/*for all rows*/
		int current_rc = row_constraints[i].constraint;
		node* temp_arr = new node[current_rc]; int pos = 0;

		while(current_rc) {
			node temp = col_heap.extractMin();/*basically extract Max*/

			matrix[i][temp.index] = game_piece;
			output.push_back(make_pair(i,temp.index));

			if(temp.constraint - 1 > 0) {
				temp.constraint = temp.constraint - 1;
				temp_arr[pos] = temp;
				pos++;
			}
			current_rc--;
		}

		for(int k = 0; k< pos; k++) {
			col_heap.insertKey(temp_arr[k]);
		}

	}

	/*Printing Output*/
	for(int i = 0; i< output.size(); i++) {
		cout<<"("<< output[i].first + 1 << "," << output[i].second + 1 << ")" << " ";
		if(i+1 < output.size()){if(output[i].first != output[i+1].first) {cout << endl;}}
	}cout<<endl;


}
