#include <algorithm>
#include <iostream>
#include "Q5b-20100192.h"
#include <set>
#include <stack>
#include <vector>


using namespace std;
							/*
							 * I have used Krukal for building the first MST.
							 * I find the cycle made by edging an extra edge 
							 * in the MST. And then remove an edge with high-
							 * est weight from among the edges of that cycle.
							 * RUNTIME: O(NLOGM)*/

int main() {

	
	string ll;
	getline(cin, ll);
	int n = stoi(ll.substr(2));

	/*Graph*/
	node** nodes = new node*[n];
	vector<edge* > edges;
	//cout << nodes[0]-> name << "h" << endl;



	int** edge_handling = new int*[n];
	for(int i = 0; i< n; i++) {
		edge_handling[i] = new int[n];
	}




	/*lambda function*/
	auto index_of = [](string ele, char tar){
		auto semi_colon_index = 0;
		for(int k = 0; k < ele.length(); k++){
			if(ele[k] ==  tar){
				semi_colon_index = k;
			}
		}
		return semi_colon_index;
	};





	int total_cities = n;
	while(total_cities--){

		string line = " ";
		getline(cin, line);
		line.erase( remove( line.begin(), line.end(), ' ' ), line.end() ); /*removing all spaces*/



		string init = " ";
		int break_point = 0;
		vector< pair<string,int> > vec;/*neighbors = name, distance to this neighbor from mode (init)*/





		for(int i=0; i< line.length(); i++){
			if(line[i] == ':'){/*getting first ele i,e first node*/
				init = line.substr(0,i);
				break_point = i;
			}



			else if(line[i] == ',' || i+1 >= line.length()){/*processing the string after ":" for getting neighnors*/
				if(i+1 >= line.length()){ /*if string has finished*/



					/*style note : need to abstract this.*/
					string ele = line.substr(break_point+1);
					string ele_we = (ele.substr(index_of(ele,';')+1));
					int ele_weight = stoi(ele_we);
					ele = ele.substr(0, index_of(ele,';'));
					vec.push_back(make_pair(ele, ele_weight));
				}else{/*found ','*/



					/*style note : need to abstract this.*/
					string ele = line.substr(break_point+1, i-(break_point+1));
					string ele_we = (ele.substr(index_of(ele,';')+1));
					int ele_weight = stoi(ele_we);
					ele = ele.substr(0, index_of(ele,';'));
					vec.push_back( make_pair(ele, ele_weight));
				}
				break_point = i;
			}


		}
		
		/*vec = pair(name, weight)*/
		/*init = C0*/

		/*nodes[node_name]*/
		int node_name = stoi(init.substr(1));
		nodes[node_name] = new node;
		nodes[node_name]->name = node_name;
		nodes[node_name]->visited = 0;
		nodes[node_name]->prev = NULL;
		for(int i = 0; i< vec.size(); i++) {
			edge* newEdge = new edge;
			newEdge -> n1 = stoi(init.substr(1));
			newEdge -> n2 = stoi((vec[i].first).substr(1));
			newEdge -> weight = vec[i].second;
			//cout << "new edge => " << newEdge -> n1 << newEdge -> n2 << endl;
			(nodes[node_name]->edges).push_back(newEdge);

			/*duplicate edges handling*/

			if(edge_handling[newEdge->n1][newEdge->n2] != 1) {
				edges.push_back(newEdge);
				/*duplicate handling matrix filling*/
				edge_handling[newEdge->n1][newEdge->n2] = 1;
				edge_handling[newEdge->n2][newEdge->n1] = 1;
			}
		}

	}











	pair<vector<edge* >, vector<edge* > > mst_edges = minimum_spanning_tree(nodes, edges, n);/*first = discarded, second = included*/



	cout << "MST1: ";
	for(auto i: mst_edges.second) {
		cout << "(" << "C" <<i -> n1 << " , " << "C" << i -> n2 << ")" << "  "; 
	}cout <<endl;

	vector<edge *>* discarded_edges = &mst_edges.first;
	vector<edge *>* included_edges = &mst_edges.second;



	/*Adding an edge an arbitrary edge*/
	int node1 = 0, node2 = 0, new_weight = 0;

	string part = "b";
	cin >> part;//a

	int r_ind = 0;
	cin >> r_ind;

	cin >> part;//b
	cin >> node1 >> node2 >> new_weight;


	cout << "Adding (C" << node1 << " , C" 
	<< node2 << ")" << " with weight => " 
	<< new_weight << endl;


	edge* edge_to_add1 = new edge;
	edge_to_add1 -> n1 = node1;
	edge_to_add1 -> n2 = node2;
	edge_to_add1 -> weight = new_weight;
	nodes[node1] -> edges . push_back(edge_to_add1);


	edge* edge_to_add2 = new edge;
	edge_to_add2 -> n1 = node2;
	edge_to_add2 -> n2 = node1;
	edge_to_add2 -> weight = new_weight;
	nodes[node2] -> edges . push_back(edge_to_add2);


	edges . push_back(edge_to_add1);
	included_edges -> push_back(edge_to_add1);



	edge * redundant_edge =  give_edge_to_remove(included_edges, nodes[node1], nodes, n);cout << "MST2: ";

	/*cout << "Removing " << "(" << redundant_edge -> n1 << " , " 
	<< redundant_edge -> n2 << ")" << ", an edge with weight => " 
	<< redundant_edge -> weight << endl;*/


	vector<edge *>:: iterator it = included_edges -> begin();
	for(it = included_edges -> begin(); it != included_edges -> end(); it ++) {
		if(((*it) -> n1 == redundant_edge -> n1 || (*it) -> n1 == redundant_edge -> n2 ) && 
		   ((*it) -> n2 == redundant_edge -> n2 || (*it) -> n2 == redundant_edge -> n1)) {break;}
	}
	included_edges->erase(it);



	for(vector<edge *>::iterator ft = included_edges -> begin(); 
		ft != included_edges -> end(); 
		ft ++) {
		cout << "(" << "C" <<(*ft) -> n1 << " , " 
		<< "C" << (*ft) -> n2 << ")" 
		<< "  "; 
	}cout <<endl;
	return 0;
}


edge * give_edge_to_remove(vector<edge *>* included_edges, node* n1, node** nodes, int n) {
	/*included edges size => n+1*/

	vector<edge *>* cycle = new vector<edge *>;
	give_cycle(n1, nodes, n, cycle);

	sort(cycle -> begin(), cycle -> end(), is_greater);

	return (*cycle)[0];
	//for(int i = 0; i< cycle -> size(); i++) {cout << (*cycle)[i] -> weight << endl;}
}

void give_cycle(node* n1, node** nodes, int m, vector<edge *>* cycle) {
	stack<node* > s;
	s.push(n1);

	int ii = 1;
	while(ii) {
		node * n = s.top();
		s.pop();
		n -> visited = 1;
		for(int i = 0; i< n->edges . size(); i++) {
			node* next = nodes[n->edges[i] -> n2];
			if(next -> visited == 0) {
				s.push(next);
				next-> prev = n;
			}
			if(next -> visited == 1 && 
				n-> prev != next) {
				next-> prev = n;
				ii = 0;
				break;
			}
		}
	}


	/*all prev pointers are set by now*/
	node * n = n1;
	int name_n = n1 -> name;
	node * p = n1 -> prev;
	while(p -> name != n1 -> name) {
		for(int i = 0; i< p-> edges . size(); i++) {
			if(p -> edges [i] -> n2 == name_n) {
				cycle -> push_back(p -> edges [i]);
				//cout << "inserting ==> " << p -> edges[i] -> n1 << "'" << p -> edges[i] -> n2 << endl;
			}
		}
		name_n = p -> name;
		p = p -> prev;

	}
	for(int i = 0; i< p-> edges . size(); i++) {
		if(p -> edges [i] -> n2 == name_n) {
			cycle -> push_back(p -> edges [i]);
			//cout << "inserting ==> " << p -> edges[i] -> n1 << "'" << p -> edges[i] -> n2 << endl;
		}
	}


	return;
}

bool is_greater(edge* a, edge* b) {
	return a -> weight > b -> weight ? true : false;
}
