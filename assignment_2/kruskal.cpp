#include <algorithm>
#include <iostream>
#include "kruskal.h"
#include <set>
#include <vector>
#include "pqueue.cpp"

using namespace std;



pair<vector<edge* >, vector<edge* > > minimum_spanning_tree(node** nodes, vector<edge*> edges, int n) {

	/*making sets of all nodes (For cycle detection while making MST)*/
	vector<set<int> > all_sets;/*vector for all sets*/
	for(int i = 0; i< n; i++) {
		set<int>* s = new set<int>;
		s->insert(nodes[i]-> name);
		all_sets.push_back(*s);
	}


	/*Heap for storing all the edges*/
	MinHeap<edge*>* heap = new MinHeap<edge*>(edges.size(), &IsSmallEdge);
	for(int i = 0; i< edges.size(); i++) {
		heap -> insertKey(edges[i]);
	}

	vector<edge* > discarded_edges;
	vector<edge* > included_edges;
	/*edges.size == heap.size basically*/
	for(int i = 0; i< edges.size(); i++) {
		edge* extracted_edge = heap -> extractMin();



		int n1 = 0, n2 = 0;
		n1 = extracted_edge -> n1;
		n2 = extracted_edge -> n2;






		set<int > s1;set<int>* s1p = NULL; 
		set<int > s2;set<int>* s2p = NULL;
		vector< set<int> >:: iterator itr;
		bool f1 = false, f2 = false;
		for(itr = all_sets.begin(); itr != all_sets.end(); itr ++) {
			

			set<int > s = *itr;
			//cout << "s "<< s.size() << endl;
			//for(set<int>::iterator itt = s . begin(); itt != s . end(); itt ++) {cout << *itt << " ";}cout<<endl;
			
			auto p = s.find(n1);
			if(p != s.end()) {
				s1 = *itr;
				s1p = &(*itr);
				f1 = true;
			}/*else if(!f1){
				s1 = new set<int>; allocating a set so that, no seg fault due to no allocated mem
			}*/

			auto q = s.find(n2);
			if(q != s.end()) {
				s2 = *itr; 
				s2p = &(*itr);
				f2 = true;
			}/*else if(!f2){
				s2 = new set<int>;
			}*/

		}
		
		

		 
		/*cout << &s1 << " == " << &s2 << endl;*/
		bool is_same_set = false;
		if(s1 == s2) {
			
			is_same_set = true;
		}

		/*cout << n1 << "->" << n2 << endl;
		for(set<int>::iterator itt = s1p -> begin(); itt != s1p -> end(); itt ++) {cout << *itt << " ";}cout<<endl;
		for(set<int>::iterator itt = s2p -> begin(); itt != s2p -> end(); itt ++) {cout << *itt << " ";}cout<<endl;*/



		if(!is_same_set) {
			/*union the sets s1 and s2*/
			/*pour all the elements of s2 in s1, and delete all the element is s2*/
			set<int>:: iterator set_itr;
			for(set_itr = s2p->begin(); set_itr != s2p->end(); set_itr ++) {
				s1p -> insert(*set_itr);
			}

			/*erasing the elements of s2*/
			s2p -> erase(s2p -> begin(), s2p -> end());
			included_edges.push_back(extracted_edge);
		}else{
			discarded_edges.push_back(extracted_edge);
			/*take n1 and n2 and remove this edge from their edges*/
			node* node_n1 = nodes[n1];
			node* node_n2 = nodes[n2];






			vector<edge* >::iterator ite = (node_n1 -> edges) .begin();
			for(ite = (node_n1 -> edges) .begin(); ite != (node_n1 -> edges) .end(); ite ++){
				if(
					(((*ite)-> n1 == node_n1-> name) || ((*ite)-> n1 == node_n2-> name))
											  		 &&
					(((*ite)-> n2 == node_n1-> name) || ((*ite)-> n2 == node_n2-> name))				  
				  ) {break;}
			}

			(node_n1 -> edges).erase(ite);



			vector<edge* >::iterator iti = (node_n2 -> edges) .begin();
			for(iti = (node_n2 -> edges) .begin(); iti != (node_n2 -> edges) .end(); iti ++){
				if(
					(((*iti)-> n1 == node_n1-> name) || ((*iti)-> n1 == node_n2-> name))
												     &&
					(((*iti)-> n2 == node_n1-> name) || ((*iti)-> n2 == node_n2-> name))				  
				  ) {break;}
			}

			(node_n2 -> edges).erase(iti);

		}

	}


	return make_pair(discarded_edges, included_edges);
}

bool IsSmallEdge (edge* a, edge* b) {
	return a -> weight < b -> weight ? true : false;
}