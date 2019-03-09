#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <map>
#include <set>
#include <vector>
#define notSet -1

using namespace std;




/*
	T(n, cut positions) = max(for loop on all cut positions and T(x, remainging positions) on resulting lengths after cut)
	Time Complexity = O(n*m) where n = length and m = total cut positions
	Space Complexity = O(n*m)
	Total O(N*M) sub problems
	After memoization, Constant time for each problem
*/



void fillVector(string line, vector<int>& vec){
	line = line.substr(2);
	int a = 0, b = 0;


	for(int i = 0; i< line.length(); i++){
		if(line[i] == ' '){b = i;vec.push_back(stoi(line.substr(a, b-a)));a = i+1;}
		if(i == line.length()-1){vec.push_back(stoi(line.substr(a)));}
	}

}



pair<vector<int>, vector<int>> formulate(vector<int> vec, int n, int t){

	vector<int> l;
	vector<int> s;

	int le = 0, se = 0;
	se = t; le = n-t;
	for(auto i: vec){
		if(i > t){l.push_back(i-t);}
		else if(i<t){s.push_back(i);}
	}

	l.push_back(le);s.push_back(se);
	return make_pair(s, l);
}


int min(int a, int b){return a<b?a:b;}


int algo(int n, vector<int>  m, int** memo, set<int>& cols) {
	if(m.size() < 1){return 0;}
	cols.insert(n);

	int cost = INT_MAX;
	for(int i = 0; i< m.size(); i++){
		auto p = formulate(m, n, m[i]);

		int se = (p.first)[(p.first).size() -1];
		int le = (p.second)[(p.second).size() -1];
		p.first.pop_back();
		p.second.pop_back();


		int ans = 0;
		if(memo[n][m[i]] != notSet){ans = memo[n][m[i]];}
		else {ans = n + algo((se),(p.first), memo, cols) +algo((le),(p.second), memo, cols);}
		
		cost = min(cost, ans);
		memo[n][m[i]] = cost;
	}

	return cost;
}





pair<vector<pair<int, int>>, int> track(int n, vector<int>  m, int resd) {
	if(m.size() < 1){vector<pair<int, int>> emp = {};return make_pair(emp,0);}

	vector<pair<int, int>> costVec;
	int cost = INT_MAX;
	for(int i = 0; i< m.size(); i++){
		auto p = formulate(m, n, m[i]);

		int se = (p.first)[(p.first).size() -1];
		int le = (p.second)[(p.second).size() -1];
		p.first.pop_back();
		p.second.pop_back();

		
		int ans = 0;
		vector<pair<int, int>> ansVec = {};
		pair<vector<pair<int, int>>, int> firstAns = track((se),(p.first), resd);
		
		pair<vector<pair<int, int>>, int> secondAns = track((le),(p.second), resd+m[i]);


		ans = n + firstAns.second + secondAns.second;
		for(auto k: firstAns.first){ansVec.push_back(k);}
		for(auto k: secondAns.first){ansVec.push_back(k);}
		ansVec.push_back(make_pair(n+resd, m[i]+resd));


		if(cost > ans)
		{costVec.clear();for(auto k: ansVec){costVec.push_back(k);}}



		cost = min(cost, ans);

	}

	return make_pair(costVec, cost);
}




void showMemo(int** memo, int n, vector<int> header, set<int> cols){
	//sort(cols.begin(), cols.end());

	cout<< " " ;for(int i = 0; i< header.size(); i++){cout<< header[i] << "  ";}cout << endl;
	for(set<int>::iterator i = cols.begin(); i != cols.end(); i++){cout<< *(i) << "  "<< endl; }cout << endl;

	for(set<int>::iterator i = cols.begin(); i != cols.end(); i++){
		for(int j = 0; j< header.size(); j++){
			cout << memo[*i][header[j]] << " ";
		}cout<< endl;
	}

	/*for(int i = 0; i < n+1 ; i++){
		for(int j = 0; j< n+1; j++){
			cout << memo[i][j] << " ";
		}cout<< endl;
	}*/
}





vector<int> makeHeader(vector<int> m){
	vector<int> ans = {};
	for(int i = 0; i< m.size(); i++){
		ans.push_back(m[i]);
		for(int j = i+1; j< m.size(); j++){
			ans.push_back(m[j]-m[i]);
		}
	}

	sort(ans.begin(), ans.end());

	return ans;
}
int main(){


	string line;
	getline(cin, line);
	int n = stoi(line.substr(2));



	getline(cin, line);
	vector<int> m = {};
	fillVector(line, m);




	int** memo = new int*[n+1];
	for(int i = 0; i< n+1; i++){memo[i] = new int[n+1];}
	for(int i = 0; i<  n+1; i++){for(int k = 0; k< n+1; k++){memo[i][k] = notSet;}}



	set<int> cols;
	int ans = algo(n, m, memo, cols);
	

	int resd = 0;
	vector<pair<int, int>> t = track(n, m, resd).first;



	vector<int> comps = {};
	for(int i = t.size()-1; i >= 0; i--){comps.push_back(t[i].second);}


	/*vector<int> header = makeHeader(m);
	showMemo(memo, n, header, cols);*/


	cout << "Optimal cut ordering: ";
	for(auto i: comps){cout << i << " ";}cout << endl;
	cout << "Lease Cost: "<< ans << endl;
	
	
	return 0;
}
