#include <iostream>
#include <vector>
#define notSet -100
using namespace std;


/*
	T(i) = 0 if i < 0
	T(n) = max(RL[n] + T(n-1), RH[n]+ T(n-2))
	Time Complexity = O(n)
	Space Complexity = O(n)
	Total O(N) sub problems
	After memoization, Constant time for each problem
*/


int max(int a, int b){return (a>b)? a:b;}

int maxRevenue(vector<int>& RH, vector<int>& RL, int i, int* calls) {
	if(i == 0){calls[i] = max(RH[0], RL[0]);return calls[i];}
	if(i< 0){return 0;}


	if(calls[i] == notSet){
		int local_ans = 0;
		local_ans =  max(RL[i] + maxRevenue(RH, RL, i-1, calls), RH[i] + maxRevenue(RH, RL, i-2, calls));
		calls[i] = local_ans;
		return local_ans;
	}
	else {return calls[i];}
}


vector<int> maxComponents(vector<int>& RH, vector<int>& RL, int i, int* calls){
	if(i < 0){
		return {};
	}

	if(i == 0){
		return {max(RH[0], RL[0])};
	}

	if(calls[i-1] + RL[i] == calls[i]){
		vector<int> ans = maxComponents(RH, RL, i-1, calls);
		ans.push_back(RL[i]);
		return ans;
	}else {
		vector<int> ans = maxComponents(RH, RL, i-2, calls);
		ans.push_back(notSet);
		ans.push_back(RH[i]);
		return ans;
	}
}


int main(){
	string tmp = "";
	int n = 0;
	cin >> tmp;
	cin >> n;
	cin >> tmp;
	vector<int> RH = {};
	vector<int> RL = {};
	for(int i = 0; i< n; i++){
		int num = 0; cin >> num;
		RH.push_back(num);
	}
	cin >> tmp;
	for(int i = 0; i< n; i++){
		int num = 0; cin >> num;
		RL.push_back(num);
	}
	

	int calls[RH.size()]; 
	for(int i = 0; i< RH.size(); i++){calls[i] = -100;}
	int ans = maxRevenue(RH, RL, RH.size()-1, calls);
	vector<int>  components = maxComponents(RH, RL, RH.size()-1, calls);		
	//for(int i = 0; i< RH.size(); i++){cout << components[i] << " : ";}cout<<endl;

	for(int i = 0; i< RH.size(); i++){
		cout << "Week"<< i+1<< ": ";
		if(components[i] == RH[i]){cout<< "High "<< RH[i]<<endl;}
		else if(components[i] == RL[i]){cout<<"Low "<< RL[i]<<endl;}
		else {cout<<"Priming."<<endl;}

	}
	cout <<"Max: " << ans << endl;

	return 0;
}