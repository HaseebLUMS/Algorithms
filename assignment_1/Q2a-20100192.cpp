#include <iostream>
#include "Q2-20100192.cpp"

using namespace std;


int main(){

	
	string n = " ";
	int total_leaders = 0;
	cin >> n >> total_leaders;
	cin.ignore();
	alignment* a = new alignment(total_leaders);




	while(total_leaders--){
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
		a->add_leader(init,vec);
	}



	/*arg = 1 -> part a(line)*/
	/*arg = 2 -> part b(seat)*/
	a->alignable(1);

	return 0;
}