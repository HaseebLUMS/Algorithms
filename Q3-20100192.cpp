#include <iostream>
#include "pqueue.cpp"
#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;


						/***********************************************************************
						*	I have used Dijkestra for calculating shortest paths. By this my 
						*	time complexity is simple O(ElogV). The space complexity is simple
						*	O(E+V). 
						*	I just calculate shortest paths form source to destination and from
						*	sourc to scene and from scene to destination. 
						*************************************************************************/


struct edge;
struct node{
	string name;
	int distance;
	node * prev;
	vector<edge*> edges;
};
struct edge{
	node* origin;
	node* destination;
	string dest_name;
	int weight;	
};








class graph{
public:
	graph(int length);
	void add_node(string name, vector<pair<string, int> > vec);
	void Dijkestra(string st_node, string en_node); /*will store path in vec and return total weight of graph*/
	void Solution(string from, string to, string scene);
private:
	vector<node*> nodes;
	int max_nodes;
	int total_nodes;
	map<string, node*> m;
	vector<edge*> all_edges;
};





graph::graph(int length){
	max_nodes = length;
	total_nodes = 0;
}





void graph::add_node(string name, vector<pair<string, int> > vec){
	if(total_nodes == max_nodes)
		return;




	node* n = new node;
	n -> name = name;
	n -> distance = 0;
	n -> prev = NULL;





	for(auto i: vec){
		//cout<< i.first <<endl;
		edge* new_ed = new edge;
		new_ed-> origin = n;
		new_ed-> destination = NULL;
		new_ed-> dest_name = i.first;
		new_ed-> weight = i.second;
		n -> edges.push_back(new_ed);
		all_edges.push_back(new_ed);
	}



	/*Do I really need this check?*/
	if(vec.size() < 1){/*if it has no edges*/
		n->edges = {};
	}



	nodes.push_back(n);
	m.insert(make_pair(name,n));
	total_nodes++;





	if(total_nodes == max_nodes){
		for(auto ed: all_edges){
			ed->destination = m.find(ed->dest_name)->second;//s->second because find gives an iterator i.e ptr
		}
	}





	return;
}



bool IsLessNode(node * a, node * b){
	return a->distance < b->distance;
}




int indexOf(node*n, node** arr, int s){
	for(int i=0; i< s; i++){
		if(arr[i]->name == n->name){
			return i;
		}
	}
	return -1;
}


void graph::Dijkestra(string st_node, string en_node){
	vector<string> vec;//for path
	if(m.find(st_node) == m.end()){
		return;
	}



	node* fromPlace = m.find(st_node)->second;
	node* toPlace = m.find(en_node)->second;
	if (toPlace->name == fromPlace->name){
		return;
	}





	vector<node*> dijkstraPath;
	for (int i = 0; i < nodes.size(); ++i){
		nodes[i]->prev = NULL;
		if (nodes[i]->name	== st_node)
			nodes[i]->distance = 0;
		else 
			nodes[i]->distance = 2147483640;//seven less than biggest 32 bit int
	}





	MinHeap<node*> path(nodes.size(),&IsLessNode);
	for (int i = 0; i < nodes.size(); ++i){
		path.insertKey(nodes[i]);
	}





	int enough = 0;
	while(path.getHeapSize() && !enough){

		node* a = path.extractMin();

		for(auto i: a->edges){
			if(i->weight + a->distance < i->destination->distance){
				i->destination->distance = i->weight + a ->distance;

				int ind = indexOf(i->destination ,path.getHeap(),path.getHeapSize());
				path.decreaseKey(ind,i->destination);
				i->destination->prev = a;
			}
			if(i->destination->name == en_node && i-> origin -> name == st_node){
				enough = 1;
				break;
			}
		}
	}




}



int dist(node* s, node* p){
	for(auto i: s->edges){
		if(i->destination == p){
			return i->weight;
		}
	}
	cout<<"Here Error"<<endl;
	return -1;
}



void graph::Solution(string from, string to, string scene){

	cout<<"To: "<<to<<"\nFrom: "<<from<<endl;
	Dijkestra(from, to);
	int total_distance = 0;
	vector<string> from2to;
	node* toTemp = m.find(to)->second;
	if(toTemp == NULL){cout<<"Masla"<<endl;}
	cout<<toTemp <<endl;
	cout<<"Start"<<endl;
	while(toTemp){
		from2to.push_back(toTemp->name);
		
		if(toTemp->prev != NULL){
			total_distance += dist(toTemp->prev, toTemp);//SEG FAULT
		}
		toTemp = toTemp->prev;
	}



	Dijkestra(from, scene);
	int mid1_distance = 0;
	vector<string> from2mid;
	toTemp = m.find(scene)->second;
	while(toTemp){
		from2mid.push_back(toTemp->name);
		
		if(toTemp->prev != NULL)
			mid1_distance += dist(toTemp->prev, toTemp);//SEG FAULT
		toTemp = toTemp->prev;
	}





	//cout<<scene<<"->"<<to<<endl;
	Dijkestra(scene, to);
	int mid2_distance = 0;
	vector<string> mid2to;
	toTemp = m.find(to)->second;
	while(toTemp){
		mid2to.push_back(toTemp->name);
		
		if(toTemp->prev != NULL)
			mid2_distance += dist(toTemp->prev, toTemp);//SEG FAULT
		toTemp = toTemp->prev;
	}
	if((0.2*total_distance)+total_distance >= (mid1_distance+mid2_distance)){
		cout<<"Yes."<<endl;
	}else{
		cout<<"No"<<endl;
	}


	reverse(from2to.begin(), from2to.end());
	reverse(from2mid.begin(), from2mid.end());
	reverse(mid2to.begin(), mid2to.end());
	cout<<"Shortest Path between "<<from <<" and "<<to<<" with distance "<<total_distance<<" :"<<endl;
	for(auto i: from2to){
		cout<<i<<"->";
	}cout<<endl;
	cout<<"Shortest Path between "<<from <<" and "<<to<<" via "<<scene<<" with distance "<<mid2_distance+mid1_distance<<" :"<<endl;
	for(auto i = 0; i< from2mid.size()-1; i++){
		cout<<from2mid[i]<<"->";
	}
	for(auto i: mid2to){
		cout<<i<<"->";
	}cout<<endl;
}









int main(){


	string n = " ";
	int total_cities = 0;
	cin >> n >> total_cities;
	cin.ignore();
	graph* g = new graph(total_cities);




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





	while(total_cities--){


		string line = " ";
		getline(cin, line);
		line.erase( remove( line.begin(), line.end(), ' ' ), line.end() ); /*removing all spaces*/



		//cout<<"Final line: "<<line<<endl;
		string init = " ";
		int break_point = 0;
		vector< pair<string,int> > vec;/*neighbors = name, distance to this neighbor from mode (init)*/





		for(int i=0; i< line.length(); i++){
			if(line[i] == ':'){/*getting first ele i,e first node*/
				//cout<<":st"<<endl;
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
		
		g->add_node(init,vec);
	}


	cout<<"Enter FROM, TO, VIA"<<endl;
	string from, to, scene;
	cin>>from>>to>>scene;
	g->Solution(from, to, scene);
	return 0;
}