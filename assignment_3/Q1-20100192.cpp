#include "Q1-20100192.h"

//Input will be of the form
//A1, A2, ....


								/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
								*	I have used Gale Shapley Algorithm for solving this problem. 
								*	The time complexity is O(n^2). Space complexity is O(n^2) too.
								*	It is a typical Gale Shapley so no need to explain the algo.
								*	Arrays are used as data structure.
								** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



int main(int argc, char const *argv[])
{
	/*Data Structures*/
	int n;
	int** planePreferences; //preferences of planes about ports
	int** portPreferences; //prefernces of ports about planes
	vector<invalid> X;

	/*Reading Input*/
	fileReading(n, planePreferences, portPreferences, X);
	
	//File Read Test
	/*{
		cout << "\nplanePreferences\n"<< endl;
		for(int i = 0; i< n; i++) {
			for (int j = 0; j < n; j++) {
				cout << planePreferences[i][j] << " ";
			}cout << endl;
		}
		cout << "\nportPreferences\n"<< endl;
		for(int i = 0; i< n; i++) {
			for (int j = 0; j < n; j++) {
				cout << portPreferences[i][j] << " ";
			}cout << endl;
		}
		cout << "\nX\n"<<endl;
		for(int i = 0; i< X.size(); i++) {
			cout << "P" << X[i].plane << " A" << X[i].port << endl; 
		}
	}*/

	

	/*Calling MAIN ALGORITHM*/
	GaleShapley(n, planePreferences, portPreferences, X);	





	return 0;
}

void GaleShapley(int n, int** &planePreferences, int** &portPreferences, vector<invalid> X) {

	/*Ports will be fix, and planes will move around*/

	vector<plane_st> not_matched_planes; //actual planes
	vector<plane_st> hanger_rejected_planes;

	vector<port_st> ports_with_preferences; //actual ports
	for(int i = 0; i< n; i++) {
		plane_st p; port_st pt;
		p.id = i;p.tries = 0; pt.id = i; pt.accomodated_plane.id = -1;
		not_matched_planes.push_back(p); ports_with_preferences.push_back(pt);
	}

	vector<plane_st> tmp_del;

	while(not_matched_planes.size() > 0 || tmp_del.size() > 0) {
		/*insert temporarily deleted elements in the vector now*/
		for(int i = tmp_del.size() -1; i> -1; i--) {not_matched_planes.push_back(tmp_del[i]);}
		tmp_del.clear();



		for(int i = not_matched_planes.size()-1; i > -1; i--) {
			int current_plane = not_matched_planes[i].id;
			int current_tries = not_matched_planes[i].tries;
			int* current_preferences = planePreferences[current_plane];
			int current_port_to_attempt = current_preferences[current_tries];

			/*Increamenting the parameters*/
			not_matched_planes[i].tries++;



			/*checking for complatibility*/
			if(!is_compatible(current_plane, current_port_to_attempt, X)) {
				if(current_tries > n-1){hanger_rejected_planes.push_back(not_matched_planes[i]);}
				else {tmp_del.push_back(not_matched_planes[i]);}
				not_matched_planes.pop_back();continue;
			}
			

			/*now placing the plane at port and dealing with ports' concerns*/
			port_st asked_port = ports_with_preferences[current_port_to_attempt];


			/*Concern 1: I already have a plane here, Please see whether I prefer you or this one.*/
			/*Concern 2: ....*/
			if(asked_port.accomodated_plane.id != -1) {
				if(!is_prefered_over_old(current_plane, asked_port.accomodated_plane.id, portPreferences[asked_port.id], n)){tmp_del.push_back(not_matched_planes[i]);not_matched_planes.pop_back();}
				else {plane_st prev = ports_with_preferences[current_port_to_attempt].accomodated_plane;ports_with_preferences[current_port_to_attempt].accomodated_plane = not_matched_planes[i];not_matched_planes.pop_back();not_matched_planes.insert(not_matched_planes.begin(), prev);i++;}
			}
			else {
				ports_with_preferences[current_port_to_attempt].accomodated_plane = not_matched_planes[i];not_matched_planes.pop_back();
			}

		}
	}



	cout<< "Stable Matching:"<<endl;
	for(int i = 0; i< ports_with_preferences.size(); i++) {
		cout << "A" << i+1 << " P" << ports_with_preferences[i].accomodated_plane.id + 1<< ", ";
	}cout<<endl;
	return;
}


bool is_prefered_over_old(int current, int old, int* portPrefs,int n) {
	int c_index = -1, o_index = -1;


	for(int i = 0; i< n; i++) {if(portPrefs[i] == current){c_index = i;}if(portPrefs[i] == old){o_index = i;}}


	if(c_index < o_index) {return true;}
	else if (c_index > o_index) {return false;}
	else {cout<<"A Major Problem."<<endl; return false;}
}


bool is_compatible(int plane, int port, vector<invalid> X) {

	for(int i = 0; i< X.size(); i++) {if(X[i].plane == plane && X[i].port == port) {return false;}}
	return true;
}


void fileReading(int& n, int** &planePreferences, int** &portPreferences, vector<invalid>& X) {
	//Reading the by delimeter

	string tmp; cin >> tmp;
	n = 0; cin >> n;


	planePreferences = new int*[n];
	portPreferences = new int*[n];
	for(int i = 0; i< n; i++) {
		planePreferences[i] = new int[n];
		portPreferences[i] = new int[n];
	}

	//Reading Planes preferences
	for(int i = 0; i< n; i++) {
		cin >> tmp; //P1:
		int* plane; //respective planes preference list
		int num = stoi(tmp.substr(1,tmp.length()-2)); // P1: ==> 1
		plane = planePreferences[num-1]; 

		for(int j = 0; j< n; j++) {
			cin >> tmp; // A1,
			int port = 0;
			if(tmp[tmp.length()-1] == ','){port = stoi(tmp.substr(1,tmp.length()-2));}
			else {port = stoi(tmp.substr(1, tmp.length()-1));}
			plane[j] = port-1;
		}
	}

	//Reading AirPorts Preferences
	for(int i = 0; i< n; i++) {
		cin >> tmp; //A1:
		int* port; //respective planes preference list
		int num = stoi(tmp.substr(1,tmp.length()-2)); // A1: ==> 1
		port = portPreferences[num-1]; 

		for(int j = 0; j< n; j++) {
			cin >> tmp; // P1,
			int plane = 0;
			if(tmp[tmp.length()-1] == ','){plane = stoi(tmp.substr(1,tmp.length()-2));}
			else {plane = stoi(tmp.substr(1, tmp.length()-1));}
			port[j] = plane-1;
		}
	}


	//Reading X
	string xLine = "";
	cin.ignore();
	getline(cin, xLine);
	xLine.erase(remove( xLine.begin(), xLine.end(), ' '), xLine.end()); //removing the spaces from the line
	int start = 0, end = 0, b = 0;
	for(int i = 0; i< xLine.length(); i++) {
		if(xLine[i] == ':') {start = i+1;}

		if(xLine[i] == ',' || i+1 >= xLine.length()) {
			if(xLine[i] == 'i'){end = i-1;}
			else {end = i;}

			string subX = xLine.substr(start, end-start+1);//P2A2
			invalid p; int A_IND = 0;
			for(int j = 0; j< subX.length(); j++) {
				if(subX[j] == 'A') {
					p.plane = stoi(subX.substr(1, j-1-1+1)) -1; //P2A2 ==> 2 ==> 1
					A_IND = j;
				}

				if(j+1 >= subX.length()) {
					p.port = stoi(subX.substr(A_IND+1, j-A_IND+1+1)) -1;
				}

			}
			X.push_back(p);
			start = i+1;
		}

	}

	return;
}