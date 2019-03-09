#include <iostream>
#include <algorithm>
#include <vector>
#include "Q2-20100192.h"
#include <utility>
#include <string>

using namespace std;
					/*
					 * "Go As Far As you can without petrol. When It is becomes
					 * necessary to refuel the fill the fuel needed for going
					 * upto the final destination."
					 * Time Complexity: O(N)
					 **/
string station_rep = "L";

int main() {
	double T = 0, R = 0, F = 0;
	int n = 0;
	string temp;


	cin >> temp >> T >> temp >> R >> temp >> F >> temp >> n;
	cout << "T: " << T << " " <<"R: "<< R << " " <<"F: "<< F << " " <<"n: "<< n <<endl;


	double distance_to_station[n+1+1];
	distance_to_station[0] = 0;


	for(int i = 1; i< n+1+1; i++) {
		cin >> temp >> distance_to_station[i];
	}
	

	minimize_the_time(T, R, F, n+2, distance_to_station);
	return 0;
}


void minimize_the_time(double T, double R, double F, int n, double* distance_to_station) {
	double remaining_petrol = T;
	int current_station = 0;
	double distance_covered_by_full_tank = T/R; 
	vector<pair<string, double> > output;
	double destination_distance = distance_to_station[n-1];


	for(int i = 0; i<= n-2; i++) {
		double remaining_petrol_after_next_station = going_to_next_station(distance_to_station[i], distance_to_station[i+1], R, remaining_petrol);
		if(remaining_petrol_after_next_station < 0) {


			double remaining_distance = destination_distance - distance_to_station[i];
			if(distance_covered_by_full_tank < remaining_distance) {
				double petrol_to_fill = T - remaining_petrol;
				double time_required = petrol_to_fill / F;


				string op = station_rep + to_string(i);
				output.push_back(make_pair(op, time_required));


				remaining_petrol = T;
				remaining_petrol = going_to_next_station(distance_to_station[i], distance_to_station[i+1], R, remaining_petrol);
			}
			else { /*full tank is not required*/
				double petrol_to_fill = remaining_distance * R;
				petrol_to_fill -= remaining_petrol;


				double time_required = petrol_to_fill / F;
				string op = station_rep + to_string(i);
				output.push_back(make_pair(op, time_required));


				remaining_petrol += petrol_to_fill;
				remaining_petrol = going_to_next_station(distance_to_station[i], distance_to_station[i+1], R, remaining_petrol);
			

			}
		} else {
			remaining_petrol = remaining_petrol_after_next_station;
		}

	}

	/*Printing Output*/
	double total_time = 0;
	for (auto k : output) {
		cout << k.first << " " << k.second << ", ";
		total_time += k.second;
	}cout << endl;
	cout << "Time Required : " << total_time << endl;
}


double going_to_next_station(double current_station, double next_station, double R, double remaining_petrol) {
	double distance_to_cover = next_station - current_station;
	double petrol_consumed = distance_to_cover * R;

	return remaining_petrol - petrol_consumed;
}
