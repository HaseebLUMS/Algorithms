#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
string S1 = "";
string S2 = "";
string S3 = "";




/*
T(i, j, k) = (T(i-1, j, k-1) if I == K, T(i, j-1, k-1) if J == K ) , if (I == J == K)(T(i-1, j, k-1) || T(i, j-1, k-1))
Time Complexity: O(n*n)
Space Complexity: O(n*n)
Sub Problems : O(n*n)
*/



pair<bool, string>** memo;

pair<bool, string> validate(int i, int j, int k){
	if(i < 0 && j < 0){
		if(k < 0){return make_pair(true, "");}
		else {return make_pair(false, "");}
	}
	if(i < 0){
		if(S2[j] == S3[k]){
			pair<bool, string> ans = validate(i, j-1, k-1);
			return make_pair(ans.first, ans.second + " S2" + S2.substr(j, 1));
		}
		else {return make_pair(false, "");}
	}
	if(j < 0){
		if(S1[i] == S3[k]){
			pair<bool, string> ans = validate(i-1, j, k-1);
			return make_pair(ans.first, ans.second + " S1" + S1.substr(i, 1));
		}
		else {return make_pair(false, "");}
	}






	if(S1[i] == S2[j] && S1[i] == S3[k]){
		
		if(memo[i][j].second != "-1"){return memo[i][j];}
		else{	
			pair<bool, string> ans1 = validate(i-1, j, k-1);
			pair<bool, string> ans2 = validate(i, j-1, k-1);
			pair<bool, string> ans =  ans1.first ? make_pair(ans1.first, ans1.second + " S1" + S1.substr(i, 1)) : make_pair(ans2.first, ans2.second + " S2" + S2.substr(j, 1));
			memo[i][j].first = ans.first;
			memo[i][j].second = ans.second;
			return ans;
		}
	}
	else if(S1[i] != S2[j]){
		pair<bool, string> ans1;
		pair<bool, string> ans2;
		pair<bool, string> ans;
		if(memo[i][j].second != "-1"){return memo[i][j];}
		else{
			if(S1[i] == S3[k] || S2[j] == S3[k]){
				if(S1[i] == S3[k]){ans1 = validate(i-1, j, k-1);}if(S2[j] == S3[k]){ans2 = validate(i, j-1, k-1);}

				ans = ans1.first ? make_pair(ans1.first, ans1.second + " S1" + S1.substr(i, 1)): make_pair(ans2.first, ans2.second + " S2" + S2.substr(j, 1));
			}
			else {ans = make_pair(false, "");}
			memo[i][j].first = ans.first;
			memo[i][j].second = ans.second;
			return ans;
		}
	}
	else if(S1[i] == S2[j] && S1[i] != S3[k]){return make_pair(false, "");}
}



int main(){
	/*S1 = "Situated";
	S2 = "";
	S3 = "Situated";*/

	cin >> S1 >> S2 >> S3;
	int n = S2.length();

	if(S1.length() > S2.length()){n = S1.length();}


	memo = new pair<bool, string>*[n+1];
	for(int i = 0; i< n+1; i++){memo[i] = new pair<bool, string>[n];}


	for(int i = 0; i< n; i++)
	{
		for(int j = 0; j< n; j++)
		{
			pair<bool, string> s = make_pair(false, "-1");
			memo[i][j].first = false;
			memo[i][j].second = "-1";
		}
	}


	pair<bool, string> ans = validate(S1.length()-1, S2.length()-1, S3.length()-1);
	if(ans.first){
		cout << " Valid" << endl<< ans.second << endl;
	}
	else {
		cout << "Invalid" << endl;
	}
	return 0;
}
