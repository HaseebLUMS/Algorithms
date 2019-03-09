#include <algorithm>
#include <iostream>
#include <limits.h>
#include <vector>
#define notSet INT_MIN
using namespace std;




/*
	T(n) = max(Set1Vals + [n] + T(n-1), Set2Vals + [n] + T(n-1))

	Time Complexity: O(n*K) after memoization
	Space Complexity: O(n)

	Constant Time for each problem

*/





void fillVector(string line, vector<int>& vec){
	line = line.substr(2);
	int a = 0, b = 0;


	for(int i = 0; i< line.length(); i++)
	{
		if(line[i] == ' '){b = i;vec.push_back(stoi(line.substr(a, b-a)));a = i+1;}
		if(i == line.length()-1){vec.push_back(stoi(line.substr(a)));}
	}

}

pair<bool, vector<int>> algo(vector<int>& arr, int i, int c_sum, int o_sum, int k, int* memo){
	if(i < 0)
	{
		if((c_sum-o_sum) == k || (o_sum - c_sum) == k){vector<int> emp = {};return make_pair(1, emp);}
		else {vector<int> emp = {};return make_pair(0, emp);}
	}



	pair<bool, vector<int>> inc = algo(arr, i-1, c_sum + arr[i], o_sum, k, memo);
	pair<bool, vector<int>> exc = algo(arr, i-1, c_sum, o_sum + arr[i], k, memo);


	
	if(inc.first){inc.second.push_back(arr[i]);return inc;}
	else {return exc;}

}


int main(){
	string line;
	getline(cin, line);
	int k = stoi(line.substr(2));



	getline(cin, line);
	vector<int> arr = {};
	fillVector(line, arr);
	int n = arr.size();




	int* memo = new int[n];
	for(int i = 0; i< n; i++){memo[i] = notSet;}



	pair<bool, vector<int>> ans = algo(arr, n-1, 0, 0, k, memo);



	/*Priting Formated Output*/
	if(ans.first){cout << "Possible."<<endl;}
	else {cout << "Not Possible." << endl; return 0;}



	int totalSum1 = 0;
	cout << "First Set: ";
	for(auto i: ans.second){cout << i << " "; totalSum1 += i;
	}cout << "sum: "<< totalSum1<< endl;
	


	int totalSum2 = 0;
	cout << "Second Set: ";
	for(auto i: arr){bool found = false;for(auto k: ans.second){if(i == k){found = true;}}if(!found){cout << i << " "; totalSum2 += i;}
	}cout << "sum: "<< totalSum2 << endl;
	



	if(totalSum2 > totalSum1){cout << "Difference: "<< totalSum2 << "-" << totalSum1 << " = " << totalSum2 - totalSum1 << endl;}
	else{cout << "Difference: "<< totalSum1 << "-" << totalSum2 << " = " << totalSum1 - totalSum2 << endl;}

	return 0;
}
