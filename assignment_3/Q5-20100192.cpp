#include "Q5-20100192.h"

								/*
								*	Recurrance Relation: T(n) = 2T(n/2) + c.n (with T(1) = 1) 
								*	Time Complexity: O(nlogn), Space Complexity: O(n)
								*	Data Structure Used: Arrays and Unordered Maps
								*/


int main() {
	int arr_size = 15;
	cout<< "n: "; cin>> arr_size;
	int m = arr_size-1;
	cout<<"m: "; cin >> m;
	int arr[arr_size];
	for(int i = 0; i< arr_size; i++){
		int ele = rand()%m;
		arr[i] = ele;
	}
	cout<<"Original: "<<endl;
	for(int i = 0; i< arr_size; i++){
		cout << arr[i] << " ";
	}cout<<endl;
	image_decomposer(arr, arr_size);
	return 0;
}



string decode(int a, int b) {
	return (a == b) ? "Y" : "N";
}




void image_decomposer(int* arr, int arr_size) {
	int ans = DnC_decomposer(arr, arr_size);
	int times = 0;
	vector<int> indices;
	for(int i = 0; i< arr_size; i++){if(arr[i] == ans){times++;indices.push_back(i);}}

	if(times > arr_size/2) {cout << "Success."<<endl;for(auto i: indices){cout<< i << " ";}cout<<endl;}
	else {cout<< "Failure." << endl;}
}




int DnC_decomposer(int* arr, int arr_size) {
	if(arr_size == 2) {string ans = decode(arr[0], arr[1]);if(ans == "Y"){return arr[0];}if(ans == "N"){return -1;}}


	if(arr_size < 2){return arr[0];}

	int* arr1 = new int[arr_size/2];
	int* arr2 = new int[arr_size - (arr_size/2)];


	for(int i = 0; i< arr_size/2; i++) {arr1[i] = arr[i];}
	for(int i = arr_size/2; i< arr_size; i++){arr2[i - (arr_size/2)] = arr[i];}


	int ans1 = DnC_decomposer(arr1, arr_size/2);
	int ans2 = DnC_decomposer(arr2, arr_size - (arr_size/2));


	if(ans1 == ans2 && ans2 != -1) {return ans1;}


	unordered_map<int,int> m;
	for(int i = 0; i< arr_size; i++){m[arr[i]] += 1;}


	int max = 0;int max_ele = 0;
	for(auto i: m) {if(i.second > max) {max = i.second; max_ele = i.first;}}
	return max_ele;
}