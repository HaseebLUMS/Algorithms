#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <stack>
#include <set>

using namespace std;

							/**********************************************************************************
							*	It uses topological sort for part 1 and prints in-recursion nodes for cycle
							*	if needed. The time complexity is simple O(n+m*logm). Like before, it is
							*	also O(n+m) if I make the assumption on input. But I have preffered to not 
							*	make any assumption for increasing the usability of my code. I have used map
							*	for storing the graph because I can search for nodes i graph by simple log(n)
							*	operations. The space complexity is O(n+m) as I have used map for storing no-
							*	des and each node has some neighbours. I have used a vector also but still the
							*	space complexity remains O(n+m).
							*
							*	In part 2, I have used the strategy of assigning level x+1 to each node if the
							*	level of its parent is x. This way I can make people sit in row number equal to
							*	level assigned to them. I have used simple BFS for that and the time complexity
							*	is O(n+m*logm). The space somplexity is O(n+m).
							**************************************************************************************/





struct leader{
	string name;
	int status; /* -1 -> not visited, 0 -> in recursion, 1 -> done*/
	vector<string> grudges;
	int level;
};



class alignment{
private:
	map<string,leader>* persons;
	int total_persons;
	int max_persons;
	int max_level;
	stack<string>* topological_sorting;
	set<string>* all_grudged;
	void increase_levels(leader * temp, int new_level);
	void component_alignable_recursive(leader* init, vector<string>& visiting, bool& able, int level, int mode);
	void component_alignable(int starting_map_index, vector<string>& visiting, bool& able, int mode);
public:
	alignment(int total_persons);
	void add_leader(string name, vector<string> grudges);
	void alignable(int mode);
};


alignment::alignment(int total){
	total_persons = 0;
	max_persons = total;
	persons = new map<string, leader>;
	topological_sorting = new stack<string>;
	all_grudged = new set<string>;
}

void alignment::add_leader(string name, vector<string> grudges){
	if(total_persons == max_persons)
		return;
	

	for(auto i: grudges){
		all_grudged->insert(i);
	}
	
	if(grudges.size() == 1 && (grudges[0] == "" || grudges[0] == " ")){
		grudges.pop_back();
	}

	leader tmp = {name,-1,grudges,-1};
	persons -> insert(make_pair(name,tmp));
	total_persons++;
}

void alignment::component_alignable_recursive(leader* init, vector<string>& visiting, bool & ans, int level, int mode){
	init -> status = 0;
	init -> level = level;
	visiting.push_back(init -> name);


	for(auto i: (init -> grudges)){
		auto temp = &((*persons)[i]);
		if(temp -> status == -1){
			component_alignable_recursive(temp, visiting, ans, level + 1, mode);
			if(ans == 1)
				visiting.pop_back();
		}else{
			if(temp -> status == 0){
				visiting.push_back(temp -> name);
				//ans = 0;
				ans = false;
				return;
			}
			if(mode == 2 && temp -> status == 1 && temp -> level < level + 1){
				increase_levels(temp, level + 1);
			}
		}
	}




	init -> status = 1;
	if(init -> level > max_level)
		max_level = init -> level;
	topological_sorting->push(init -> name);
	return;
}

void alignment::increase_levels(leader* temp, int new_level){
	temp -> level = new_level;
	for(int i = 0; i< temp -> grudges.size(); i++){
		auto neigh = &(*persons)[temp->grudges[i]];

		if(neigh -> status == 1 && neigh -> level < new_level + 1){
			increase_levels(neigh, new_level + 1);
		}
	}
	if(new_level > max_level)
		max_level = new_level;
}

void alignment::component_alignable(int starting_map_index, vector<string>& visiting, bool& able, int mode){
	
	map<string, leader>::iterator it = persons->begin();
	for(int i=0; i< starting_map_index; i++)
		it++;
	int level = 0;
	component_alignable_recursive(&(it -> second), visiting, able,level, mode);
	return;
}

void alignment::alignable(int mode){
	

	bool able = 1;
	vector<string> visiting;
	auto temp = persons->begin();



	for(int i=0; i< persons->size(); i++){
		if(able == 1 && temp->second.status == -1){
			visiting.clear();
			component_alignable(i,visiting,able, mode);
			
		}
		temp++;
	}




	if(able == true){

		cout<<"Yes"<<endl;
		if(mode == 1){
			while(!topological_sorting->empty()){

				cout<<topological_sorting->top() <<" ";
				topological_sorting->pop();
			}
			cout<<endl;
		}
		else{
			cout<<max_level+1<<endl;
			int current_level = 0;
			vector<string>* arr = new vector<string>[max_level+1];

			while(!topological_sorting->empty()){
				auto l = (*persons)[topological_sorting->top()].level;
				arr[l].push_back(topological_sorting->top());
				topological_sorting->pop();
			}
			
			for(int i=0; i< max_level+1; i++){
				for(auto k: arr[i]){
					cout<<k<<" ";
				}cout<<endl;
			}

		}
	}


	if(able == false){
		cout<<"No"<<endl;
		for(int i=0; i< visiting.size(); i++){
			cout<<visiting[i]<<"->";
		}cout<<endl;
	}
}


// int main(){

	
// 	string n = " ";
// 	int total_leaders = 0;
// 	cin >> n >> total_leaders;
// 	cin.ignore();
// 	alignment* a = new alignment(total_leaders);




// 	while(total_leaders--){
// 		string line = " ";
// 		getline(cin, line);
// 		line.erase( remove( line.begin(), line.end(), ' ' ), line.end() );
// 		string init = " ";
// 		int break_point = 0;
// 		vector<string> vec;
// 		for(int i=0; i< line.length(); i++){
// 			if(line[i] == ':'){
// 				init = line.substr(0,i);
// 				break_point = i;
// 			}
// 			if(line[i] == ',' || i+1 >= line.length()){
// 				if(i+1 >= line.length()){
// 					vec.push_back(line.substr(break_point+1));
// 				}else{
// 					vec.push_back( line.substr(break_point+1, i-(break_point+1)));
// 				}
// 				break_point = i;
// 			}
// 		}
// 		a->add_leader(init,vec);
// 	}



// 	/*arg = 1 -> part a(line)*/
// 	/*arg = 2 -> part b(seat)*/
// 	a->alignable(2);

// 	return 0;
// }