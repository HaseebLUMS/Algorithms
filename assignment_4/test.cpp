#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>
using namespace std;
pair<vector<int>, vector<int>> formulate(vector<int> vec, int n, int t){

	vector<int> l;
	vector<int> s;

	int le = 0, se = 0;

	se = t; le = n-t;

	for(auto i: vec){
		if(i > t){l.push_back(i-t);}
		else if(i<t){s.push_back(i);}
	}

	l.push_back(le);
	s.push_back(se);

	return make_pair(s, l);

}

int main(){
	pair<vector<int>, vector<int>> ans = formulate({3, 5, 10}, 15, 5);
	int se = ans.first[ans.first.size()-1];
	ans.first.pop_back();
	
	int le = ans.second[ans.second.size()-1];
	ans.second.pop_back();

	cout<<se << " s: "<<endl;
	for(int i = 0; i< ans.first.size(); i++){cout<< ans.first[i] << " ";}cout<<endl;
		cout<< le << " l: "<<endl;
	for(int i = 0; i< ans.second.size(); i++){cout<< ans.second[i] << " ";}cout<<endl;


}