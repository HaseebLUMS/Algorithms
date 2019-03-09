#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;



				   /*****************************************************************************
					* It uses DFS for dividing all the nodes in two bins (vectors) by assigning 
					* each node the name of bin it should go into. Then it sees for any 
					* contradiction by seeing if any already assigned node is getting assigned 
					* another bin. It takes the in-recursion nodes for printing the cycle if
					* needed. Otherwise, it prints the content of two bins. The time complexity
					* of my algorithm is O(n + m*logm). It is n+m actually if I make the assum-
					* ption that my nodes name will always be like CX , X representing a unique
					* number. I have not made this assumption as it clearly put constraints on 
					* usage but I have wriiten it to work for any type of input. Thus, my code
					* is more usable and abstarct. I have used map for storing graph. It helps
					* me to find nodes in logarithmic time. And I have used a vector for stor-
					* ing any disconnected nodes in graph. So overall space complexity is of
					* a map and vector, which is basically O(n+m) as for every n their are 
					* few neighbors stored in nodes vector reactive_to. 
					******************************************************************************/


struct node{
	bool exposed;
	bool visited;
	int bin; /*Two Bins; 0 and 1*//* -1 = undefind bin */
	node* back_ptr;
	string name;
	vector<string> reactive_to;
};





class graph{
private:
	map<string,node>* chemicals;
	int total_nodes;
	int max_length;
	vector<string>* disconnected;
	bool component_packable(int component_index_in_chemicals, vector<string>& zero_bin, vector<string>& one_bin, vector<string>& odd_cycle);
public:
	graph(int length);
	void add_node(string name, vector<string> reactive_to);
	void packable();
};

graph::graph(int length){
	max_length = length;
	disconnected = new vector<string>;
	chemicals = new map<string,node>;
	total_nodes = 0;

}

void graph::add_node(string name, vector<string> reactive_to){
	bool visit = false;


	if(total_nodes == max_length)
		return;
	if(reactive_to.size() == 1 && (reactive_to[0] == "" || reactive_to[0] == " ")){
		disconnected->push_back(name);
		visit = true;
	}


	node temp = {false,visit,-1,NULL,name,reactive_to};
	chemicals->insert(make_pair(name,temp));
	total_nodes++;
	return;

}

bool graph::component_packable(int component_index_in_chemicals, vector<string>& zero_bin, vector<string>&one_bin,vector<string>& odd_cycle){
	stack<node* > s;
	map<string,node>::iterator iter = chemicals->begin();
	for(int i=0; i< component_index_in_chemicals; i++){
		iter++;
	}
	node* it = &((iter)->second);


	s.push(it);
	it->bin = 0;
	it->visited = true;
	bool contradiction_found = false;


	while(!s.empty()){
		auto temp = s.top();
		if(temp->bin == 0){
			zero_bin.push_back(temp->name);
		}else if(temp->bin == 1){
			one_bin.push_back(temp->name);
		}



		odd_cycle.push_back(temp->name);
		if(temp->exposed){
			return false;
		}
		temp->exposed = true;



		int recent_additions = 0;
		s.pop();
		for(int i=0; i < temp->reactive_to.size(); i++){

			auto neigh = &((*chemicals)[ temp->reactive_to[i] ]);
			if(contradiction_found == false){
				if(neigh -> visited == false){
					recent_additions++;
					neigh -> visited = true;
					neigh -> back_ptr = temp;
					neigh -> bin = !(temp->bin);
					s.push(neigh);
				}else{
					if(neigh -> bin == temp -> bin){
						temp -> visited = false;
						contradiction_found = true;
						while(recent_additions--){
							s.pop();
						}
						s.pop(); //popping temp
						s.push(neigh);
						break;
					}
				}
			}else{
				if(neigh -> visited == true){
					s.push(neigh);
				}
			}
		}
	}

	return true;

}

void graph::packable(){


	vector<string> zero_bin;
	vector<string> one_bin;
	vector<string> odd_cycle;
	int component_index_in_chemicals = 0;
	bool first_component_packable = component_packable(component_index_in_chemicals,zero_bin,one_bin,odd_cycle);
	if(first_component_packable == false){
		cout<<"No"<<endl;
		for(auto i: odd_cycle){
			cout<<i<<"->";
		}cout<<endl;
		return;
	}
	map<string, node>::iterator it = chemicals->begin();
	while(it != chemicals->end()){

		int index_of_unvisited = 0;
		for(it = chemicals->begin(); it != chemicals->end(); it++){

			if(it->second.visited == false){
				component_index_in_chemicals = index_of_unvisited;
				break;
			}

			index_of_unvisited++;

		}
		if(it == chemicals->end())
			break;
		first_component_packable = component_packable(component_index_in_chemicals,zero_bin,one_bin,odd_cycle);
		if(first_component_packable == false){
			cout<<"No"<<endl;
			for(auto i: odd_cycle){
				cout<<i<<"->";
			}cout<<endl;
			return;
		}

	}

	cout<<"Yes"<<endl;

	for(auto i: zero_bin)
		cout<<i<<" ";
	cout<<endl;

	for(auto i: one_bin)
		cout<<i<<" ";

	for(int i=0; i< disconnected->size(); i++)
		cout<<(*disconnected)[i]<<" ";
	cout<<endl;

}

int main(){


	string n = " ";
	int total_chemicals = 0;
	cin >> n >> total_chemicals;
	cin.ignore();
	graph* g = new graph(total_chemicals);




	while(total_chemicals--){


		string line = " ";
		getline(cin, line);
		line.erase( remove( line.begin(), line.end(), ' ' ), line.end() );


		string init = " ";
		int break_point = 0;
		vector<string> vec;



		for(int i=0; i< line.length(); i++){
			
			if(line[i] == ':'){
				init = line.substr(0,i);
				break_point = i;
			}


			if(line[i] == ',' || i+1 >= line.length()){
				if(i+1 >= line.length()){
					vec.push_back(line.substr(break_point+1));
				}else{
					vec.push_back( line.substr(break_point+1, i-(break_point+1)));
				}
				break_point = i;
			}


		}
		g->add_node(init,vec);
	}


	g->packable();
	return 0;
}