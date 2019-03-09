#include "Q4-20100192.h"




							/*
							*	I have used divide and conquer for this problem. My time complexity is O(n)
							*	Space complexity is also O(n). I have used arrays as a data structure.
							*	I have made commments in the major funtion maximum_ancestry() and my
							*	algo is clearly mentioned there.
							*	T(n) = 2*T(n/2) + c
							*/




int main() {

	/*int arr_size = 7;
	int arr[arr_size] = {7,6,5,4,3,2,1};*/


	/*int arr_size = 15;
	int arr[arr_size] = {17, 20, 4, 5, 7, 35, 6, 3, 6, 16, 12, 18, 1, 2, 3};*/

	
	int arr_size = 15;
	cout << "Enter arr-size: "; cin >> arr_size; //cout<< "arr-size is "<< arr_size << endl;
	int arr[arr_size];
	

	int decision = 0;
	cout<< "Enter 0 for random arr and 1 for entering the array yourself: "; cin >> decision;
	

	srand(5);
	if(decision != 0) {int ele = 0;for(int i = 0; i< arr_size; i++){cin >> ele;arr[i] = ele;}}
	else {for(int i = 0; i< arr_size; i++){int rn = 0; rn = rand()%50; arr[i] = rn;}}

	//for(int i = 0; i< arr_size; i++){cout<<arr[i]<<endl;}


	node* ptr_arr[arr_size];


	node* parent_node = new node;
	parent_node->id = 0;parent_node->value = arr[0];
	parent_node->total_sum = -1; parent_node->side_sum = -1; parent_node->leave[0].id = -1; parent_node->leave[0].name = -1; parent_node->leave[1].name = -1; 
	parent_node->leave[1].id = -1; parent_node->left = NULL; parent_node->right = NULL;
	parent_node->vecs[0] = NULL; parent_node->vecs[1] = NULL;

	ptr_arr[parent_node->id] = parent_node;


	for(int i = 1; i< arr_size; i++) {
		
		node* new_child = new node;
		new_child->id = i;new_child->value = arr[i]; new_child->total_sum = -1;new_child->side_sum = -1;new_child->leave[0].id = -1;new_child->leave[1].id = -1; 
		new_child->left = NULL;new_child->right = NULL;
		new_child->vecs[0] = NULL; new_child->vecs[1] = NULL;
		
		new_child->leave[0].name = i; 
		new_child->leave[1].name = i;
		
		ptr_arr[i] = new_child;

		int pid = (i-1)/2; //index of parent in array
		if(ptr_arr[pid]->left == NULL){ptr_arr[pid]->left = new_child;}
		else{ptr_arr[pid]->right = new_child;}

	}
	//print_tree(parent_node);


	/*Balances Tree is ready at this moment ; Stored in parent_node*/

	maximum_ancestry(parent_node);


	/*making child number from index of array*/
	int total_children = (arr_size+1)/2;
	int total_not_children = arr_size - total_children;
	int child_0_index = arr_size - total_children;


	/*Priting OutPut*/
	cout << "x(i) = x"<< parent_node->leave[0].name - total_not_children  + 1<<endl;
	cout << "x(j) = x"<< parent_node->leave[1].name - total_not_children + 1<<endl;



	cout << "Value of nodes in ancestry in x"<< parent_node->leave[0].name - total_not_children + 1 << " : { ";
	for(int i=0; i< parent_node->vecs[0]->size(); i++) {
		cout << (*(parent_node->vecs[0]))[i] << ", ";
	}cout<<" }"<<endl;



	cout << "Value of nodes in ancestry in x"<< parent_node->leave[1].name - total_not_children + 1 << " :{ ";
	for(int i=0; i< parent_node->vecs[1]->size(); i++) {
		cout << (*(parent_node->vecs[1]))[i] << ", ";
	}cout<<" }"<<endl;


	/*counting total ancestry*/
	int total = 0;
	for(int i = 0; i< parent_node->vecs[0]->size(); i++) {
		if((*(parent_node->vecs[0]))[i] == ((*(parent_node->vecs[1]))[i])) {
			total += ((*(parent_node->vecs[0]))[i]);
		}else {
			total += ((*(parent_node->vecs[0]))[i]);
			total += ((*(parent_node->vecs[1]))[i]);
		}
	}

	cout << "Value of max ancestry (x"<<parent_node->leave[0].name - total_not_children + 1 << " , x"<< parent_node->leave[1].name - total_not_children + 1<<") = " << total << endl;


	return 0;
}

void maximum_ancestry(node* p) {
	//Base Case
	if(p->left->left == NULL) {
		p->total_sum = p->left->value + p->right->value + p->value;
		p->side_sum = ((p->right->value > p->left->value) ? (p->right->value) : (p->left->value)) + p->value;
		
		p->leave[0].id = p->left->value; p->leave[1].id = p->right->value;
		p->leave[0].name = p->left->id; p->leave[1].name = p->right->id;


		p->vecs[0] = new vector<int>; p->vecs[0]->push_back(p->left->value); p->vecs[0]->push_back(p->value);
		p->vecs[1] = new vector<int>; p->vecs[1]->push_back(p->right->value); p->vecs[1]->push_back(p->value);
		return;
	}



	maximum_ancestry(p->left);
	maximum_ancestry(p->right);




	/*Calculating total sum of a node (supposinf it is the answer*/
	p->total_sum = p->left->side_sum + p->right->side_sum + p->value;

	/*Calculting side sum which will be used by its parent for calculating his total_sum*/
	p->side_sum = ((p->right->side_sum > p->left->side_sum) ? (p->right->side_sum) : (p->left->side_sum)) + p->value;




	/*This field is for telling the final resulting node that what are the leaves giving optimal answer*/
	p->leave[0].id = (p->left->leave[0].id > p->left->leave[1].id) ? p->left->leave[0].id : p->left->leave[1].id;
	p->leave[0].name = (p->left->leave[0].id > p->left->leave[1].id) ? p->left->leave[0].name : p->left->leave[1].name;

	p->leave[1].id = (p->right->leave[0].id > p->right->leave[1].id) ? p->right->leave[0].id : p->right->leave[1].id;
	p->leave[1].name = (p->right->leave[0].id > p->right->leave[1].id) ? p->right->leave[0].name : p->right->leave[1].name;



	/*This is for tracking path or (ancestry nodes)*/
	p->vecs[0] = (p->left->leave[0].id >= p->left->leave[1].id) ? p->left->vecs[0] : p->left->vecs[1];
	p->vecs[1] = (p->right->leave[0].id >= p->right->leave[1].id) ? p->right->vecs[0] : p->right->vecs[1]; 




	/*checking whether one of my child is making more of a ans than me, if yes then copying his parameter to mine's*/
	bool pushed = false;
	if(p->left->total_sum + p->value > p->total_sum) {
		p->total_sum = p->left->total_sum;
		p->side_sum = p->left->total_sum;


		p->leave[0].id = p->left->leave[0].id;
		p->leave[0].name = p->left->leave[0].name;

		p->leave[1].id = p->left->leave[1].id;
		p->leave[1].name = p->left->leave[1].name;


		p->vecs[0] = p->left->vecs[0]; p->vecs[0]->push_back(p->value);
		p->vecs[1] = p->left->vecs[1]; p->vecs[1]->push_back(p->value);
		pushed = true;

	}

	if(p->right->total_sum + p->value > p->total_sum) {
		p->total_sum = p->right->total_sum;
		p->side_sum = p->right->total_sum;


		p->leave[0].id = p->right->leave[0].id;
		p->leave[0].name = p->right->leave[0].name;

		p->leave[1].id = p->right->leave[1].id;
		p->leave[1].name = p->right->leave[1].name;


		p->vecs[0] = p->right->vecs[0]; p->vecs[0]->push_back(p->value);
		p->vecs[1] = p->right->vecs[1]; p->vecs[1]->push_back(p->value);
		pushed = true;
	}

	if(!pushed) {
		 p->vecs[0]->push_back(p->value);
		 p->vecs[1]->push_back(p->value);
	}



}

void print_tree(node* p){
	if(p == NULL){return;}

	print_tree(p->left);
	cout << p->value << endl;
	print_tree(p->right);
}

