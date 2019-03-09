#include "Q2-20100192.h"



								/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
								*	I have used modified Gale Shapley Algorithm for solving this 
								*	problem. The time complexity is O(n^2). Space complexity 
								*	is O(n^2). Arrays are used as data structure.
								*	I iterate through teams locations on each day (simulated) and 
								*	update the location checking a few conditions mentioned in the
								*	manual. At the end of all days (typically 2*n), every team is set.
								** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */






int main(int argc, char const *argv[]){
	int n = 0;
	int** teamSchedule;
	string filename = argv[1];
	if(argc < 2) {
		cerr << "Provide filename in the arguments."<< endl;
		exit(0);
	}
	fileRead(filename, n, teamSchedule);
	/*{
		for(int i = 0; i< n; i++) {
			for(int j = 0; j< 2*n; j++){
				cout<< teamSchedule[i][j] + 1 << " ";
			}cout<<endl;
		}
	}*/

	int** teamPreferences = new int*[n];
	for(int i = 0; i< n; i++) {
		teamPreferences[i] = new int[n];
	} 

	int k = 0;
	for(int i = 0; i< n; i++){
		for(int j = 0; j< 2*n; j++) {
			if(teamSchedule[i][j] != -1){
				teamPreferences[i][k] = teamSchedule[i][j];
				k++;
			}
		}
		k = 0;
	}



	/*{
		cout<<"Team Preferences"<<endl;
		for(int i = 0; i< n; i++) {
			for(int j = 0; j< n; j++){
				cout<< teamPreferences[i][j] + 1 << " ";
			}cout<<endl;
		}
		cout<<"----------------"<<endl;
	}
	*/

	int** locPreferences = new int*[n];
	for(int i = 0; i< n; i++){
		locPreferences[i] = new int[n];
	}

	for(int a = 0; a< n; a++){
			int b =0;
			for(int j = (2*n)-1; j >= 0; j--){
				for(int i = 0; i< n; i++){

					if(teamSchedule[i][j] == a){locPreferences[a][b] = i;b++;}
				}
			}
	}


	/*{
		cout<<"Loc Preferences"<<endl;
		for(int i = 0; i< n; i++) {
			for(int j = 0; j< n; j++){
				cout<< locPreferences[i][j] + 1 << " ";
			}cout<<endl;
		}
		cout<<"----------------"<<endl;
	}*/


	vector<invalid> X;
	GaleShapley(n, locPreferences, teamPreferences, X);
	return 0;
}


/*void modifiesGaleShapley(int n, int** &teamPreferences) {
	int total_days = 2*n;

	vector<team> particapting_teams;
	vector<location> exacavation_locations;


	for(int i = 0; i< n; i++) {
		team t;
		t.id = i;
		t.exacavation_number = 0;
		particapting_teams.push_back(t);

		location l;
		l.id  = i;
		l.team_id = -1;
		l.is_finalised = false;
		exacavation_locations.push_back(l);
	}

	for(int i = 0; i< total_days; i++) {
		for(int j = 0; j< n; j++) {
			if(teamPreferences[j][i] != -1) {
				//teamPreferences[j][i] == location
				//cout<< "Team # "<< j+1 << "locating..."<<endl;
				if(exacavation_locations[get_location(teamPreferences[j][i], exacavation_locations)].is_finalised == false){
					//cout << "loc # " << teamPreferences[j][i] + 1<< "found free" << endl;
					exacavation_locations[get_location(teamPreferences[j][i], exacavation_locations)].team_id = j;
					particapting_teams[get_team(j, particapting_teams)].exacavation_number++;
					//cout << particapting_teams[get_team(j, particapting_teams)].exacavation_number << " inc"<<endl;
					if(particapting_teams[get_team(j, particapting_teams)].exacavation_number == n) {
						exacavation_locations[get_location(teamPreferences[j][i], exacavation_locations)].is_finalised = true;
						//cout << j + 1<< " set at " << teamPreferences[j][i] + 1<< endl;
					}
				}else {
					//ye team jahan he waheen rehney do
					//cout << j << " found " << teamPreferences[j][i] + 1<< " set already."<<endl;

					exacavation_locations[get_loc_by_team(j, exacavation_locations)].is_finalised = true;
					//cout << "So setting camp at "<< exacavation_locations[get_loc_by_team(j, exacavation_locations)].id + 1 << endl;
				}
			}
		}
	}



	for(int i = 0; i< exacavation_locations.size(); i++) {
		if(exacavation_locations[i].is_finalised) {
			//cout << "Team # " << exacavation_locations[i].team_id +1 << " @ Loc # " << exacavation_locations[i].id+1<<endl;
			cout << "L"<<exacavation_locations[i].id+1<< " T"<<exacavation_locations[i].team_id+1<<", ";
		}
	}
	cout<<endl;
	return;
}
*/
int get_loc_by_team(int team, vector<location> exacavation_locations) {
	for(int i = 0; i< exacavation_locations.size(); i++) {
		if(exacavation_locations[i].team_id == team) {
			return i;
		}
	}
	return -1;
}

int get_team(int ID, vector<team> particapting_teams) {
	for (int i = 0; i< particapting_teams.size(); i++) {
		if(particapting_teams[i].id == ID){return i;}
	}
	return -1;
}

int get_location(int ID, vector<location> exacavation_locations) {
	for (int i = 0; i< exacavation_locations.size(); i++) {
		if(exacavation_locations[i].id == ID){return i;}
	}
	return -1;
}

void fileRead(string filename, int& n, int** &teamPreferences) {
	ifstream file;
	file.open(filename.c_str());
	string tmp = ""; 
	file >> tmp >> n;
	cout<< "n: "<< n << endl;


	teamPreferences = new int*[n];
	for(int i = 0; i< n; i++) {
		teamPreferences[i] = new int[2*n]; //1 travelling day associated with each location
	}


	for(int i = 0; i< n; i++) {
		file >> tmp;
		if(tmp[tmp.length()-1] == ':') {
			int team_id = stoi(tmp.substr(1, tmp.length()-2));
			int* current_team = teamPreferences[team_id-1];

			for(int j = 0; j < 2*n; j++) {
				file >> tmp;
				

				if(tmp[0] == 'L'){
					int loc = -1;
					if(tmp[tmp.length()-1] == ','){loc = stoi(tmp.substr(1, tmp.length()-2));}
					else {loc = stoi(tmp.substr(1, tmp.length()-1));}
					current_team[j] = loc-1;
				}
				else {current_team[j] = -1;}
			

			}
		}
	}	
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
		cout << "L" << ports_with_preferences[i].accomodated_plane.id + 1 << " T" << i+1 << ", ";
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

	//for(int i = 0; i< X.size(); i++) {if(X[i].plane == plane && X[i].port == port) {return false;}}
	return true;
}
