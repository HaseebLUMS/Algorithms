#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include "Q5a-20100192.h"


using namespace std;
						/*********************************************
						 * I have Used Kruskal for buidling first MST.
						 * I store the unused edges in a vector names
						 * "discarded edges" and when an edge breaks
						 * in MST I traverse the discarded edges and
						 * find the edge connecting two partitions of
						 * the graph made by broken edge. Then I cho-
						 * ose the edge with minimum weight from the 
						 * possible candidates. 
						 * RUNTIME: O(NLOGM)
						 * ********************************************/

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


	/*Removing an arbitrary edge*/
	string part = "a";
	cin >> part;//a

	int r_ind = 0;
	cin >> r_ind;

	cin >> part;//b
	int aa = 0, bb = 0, cc = 0;
	cin >> aa >> bb >> cc;

	edge* arb = (*included_edges)[r_ind];
	cout<<"Edge Removed: "<< "(C" << arb -> n1 << " , C" << arb -> n2 << ")" << endl;
	
	vector<edge *>::iterator iter = included_edges -> begin();
	for(iter = included_edges -> begin(); iter != included_edges -> end(); iter++) {
		if(*iter == arb) {
			break;
		}
	}
	//included_edges -> pop_back();
	included_edges -> erase(iter);


	node* n1 = nodes[arb->n1];
	node* n2 = nodes[arb->n2];
	//for(vector<edge *>::iterator ft = n2 -> edges . begin(); ft != n2 -> edges . end(); ft ++){cout << (*ft) -> n1 << (*ft) -> n2 << endl;}
	vector<edge *>:: iterator it = n1->edges . begin();
	vector<edge *>:: iterator itt = n2->edges . begin();



	for(it = n1->edges . begin(); it != n1->edges .end(); it ++) {
		if((*it) -> n2 == n2 -> name){break;}
	}
	for(itt = n2->edges . begin(); itt != n2->edges .end(); itt ++) {
		if((*itt) -> n2 == n1 -> name){break;}
	}


	/*if(it == n1-> edges . end()){cout << "it == end" << endl;}
	if(itt == n2-> edges . end()){cout << "itt == end" << endl;}
	cout << "iterator "<< (*it) -> n1 << "=> " << (*it) -> n2  << endl;
	cout << "iterator "<< (*itt) -> n1 << "=> " << (*itt) -> n2  << endl;*/


	(n1 -> edges).erase(it);
	(n2 -> edges).erase(itt);/*SEG FAULT*/



	/*for(vector<edge* >::iterator i = n2-> edges . begin(); i != n2 -> edges . end(); i ++){cout << (*i)-> n1 <<"="<< (*i)-> n2 << endl;}*/


	edge* sme =  get_smallest_common_edge(discarded_edges, n1, n2, nodes, n);
	/*cout << "new edge =>> " << sme -> weight << endl;*/
	included_edges -> push_back(sme);
	cout << "MST2: ";
	for(vector<edge *>::iterator ft = included_edges -> begin(); ft != included_edges -> end(); ft ++) {
		cout << "(" << "C" <<(*ft) -> n1 << " , " << "C" << (*ft) -> n2 << ")" << "  "; 
	}cout <<endl;
	return 0;
}






edge* get_smallest_common_edge(vector<edge *>* discarded_edges,node* n1, node* n2, node** nodes, int n) {
	int flags[n];
	int mark_1 = 1, mark_2 = 2;
	for(int i = 0; i < n; i++) {
		flags[i] = 0;
	}



	traverse_and_set(n1, flags, mark_1, nodes);
	traverse_and_set(n2, flags, mark_2, nodes);
	/*cout << "Traversedd and set" << endl;
	for(int i = 0; i< n; i++) {cout << flags[i] << " ";}cout << endl;*/
	sort(discarded_edges -> begin(), discarded_edges -> end(), is_smaller_edge);
	//for(vector<edge *>::iterator ft = discarded_edges->begin(); ft != discarded_edges-> end(); ft ++){cout << (*ft) -> weight << endl;}
	

	for(vector<edge *>::iterator ft = discarded_edges->begin(); 
		ft != discarded_edges-> end(); 
		ft ++) {
		int ind_n1 = (*ft) -> n1;
		int ind_n2 = (*ft) -> n2;
		if(flags[ind_n1] != flags[ind_n2]) {
			return (*ft);
		}
	}


	cout << "no edge found" << endl;
	return NULL;


}

void traverse_and_set(node* n1, int* flags, int mark, node** nodes){
	if(!n1){return;}
	//cout << n1 -> name << endl;
	flags[n1-> name] = mark;
	for(int i = 0; i< n1-> edges . size(); i++) {
		int ind = ((n1 -> edges)[i]) -> n2;
		if(flags[ind] != mark) {
			traverse_and_set(nodes[ind], flags, mark, nodes);
		}
	}
}


bool is_smaller_edge(edge* a, edge* b) {
	return a-> weight < b -> weight ? true : false;
}
