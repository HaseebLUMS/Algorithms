#include "Q3-20100192.h"



								/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
								*	I have used Divide n Conquer Algorithm for solving this problem. 
								*	The time complexity is O(n^2). Space complexity is O(n^2) too.
								*	Recurrece relation: T(n) = 4*T(n/2) + c. Arrays are used as major 
								*	data structure.
								** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */



int bomb = 0;
string current = "";
int main() {
	int n = 0;
	cout << "Enter n: "; cin >> n; cout << endl;
	int x = 0, y = 0; cout << "Enter prohibited coordinates (e.g 0 2): "; cin >> x >> y; cout << endl;


	int** board = new int*[n]; for(int i = 0; i < n; i++) {board[i] = new int[n];}
	fillBombs(n, board, x, y);

	for(int i = 0; i< n; i++){
		for(int j = 0; j< n; j++){
			char s = 'A' + board[i][j];
			if (s == '@'){s = 'A'+ bomb+1;}
			if(i == x && j ==y){s = '0';}
			cout << s << " ";
		}
		cout<<endl;
	}

	return 0;
}

void fillBombs(int n, int** &board, int x, int y) {
	/*Base Case*/
	if(n == 2) {for(int i = 0; i< n; i++) {for(int j = 0; j< n; j++) {if(i != x || j != y) {board[i][j] = bomb;}}}bomb++;board[x][y] = -1;return;}


	int half = n/2;


	/*making four arrays*/
	int** one = new int*[n/2]; int** two = new int*[n/2]; int** three = new int*[n/2]; int** four = new int*[n/2];
	for(int i = 0; i< n/2; i++) {one[i] = new int[n/2]; two[i] = new int[n/2]; three[i] = new int[n/2]; four[i] = new int[n/2];}


	//ind(part, axis) -- 1= x-axis, 2 = y-axis
	// 1 == part one, 2 == part two, 3 == part three, 4 == part four
	int onex = ind(1,1,x,y,half);int oney = ind(1,2,x,y,half);
	int twox = ind(2,1,x,y,half);int twoy = ind(2,2,x,y,half);
	int threex = ind(3,1,x,y,half);int threey = ind(3,2,x,y,half);
	int fourx = ind(4,1,x,y,half);int foury = ind(4,2,x,y,half);

	

	fillBombs(half, one, onex, oney);
	fillBombs(half, two, twox, twoy);
	fillBombs(half, three, threex, threey);
	fillBombs(half, four, fourx, foury);



	for(int i = 0; i< n/2; i++) {for(int j = 0; j< n/2; j++) {board[i][j] = one[i][j];}}
	for (int i = 0; i < n/2; ++i){for(int j = 0; j< n/2; j++) {board[i][j+(n/2)] = two[i][j];}}
	for (int i = 0; i < n/2; ++i){for(int j = 0; j< n/2; j++) {board[i+(n/2)][j] = three[i][j];}}
	for (int i = 0; i < n/2; ++i){for(int j = 0; j< n/2; j++) {board[i+(n/2)][j+(n/2)] = four[i][j];}}


	return;
}




int ind(int part, int axis, int x, int y, int nbytwo) {

	/*check if this part contanis inherited x amd y*/
	if(x < nbytwo && y < nbytwo) {if(part == 1){if(axis == 1){return x;}if(axis == 2){return y;}}}
	if(x < nbytwo && y >= nbytwo) {if(part == 2){if(axis == 1){return x;}if(axis == 2){return y - nbytwo;}}}
	if(x >= nbytwo && y < nbytwo) {if(part == 3){if(axis == 1){return x - nbytwo;}if(axis == 2){return y;}}}
	if(x >= nbytwo && y >= nbytwo) {if(part == 4){if(axis == 1){return x - nbytwo;}if(axis == 2){return y - nbytwo;}}}

	/*assign new x and y*/
	if(part == 1){if(axis == 1){return nbytwo-1;}if(axis == 2){return nbytwo-1;}}
	if(part == 2){if(axis == 1){return nbytwo-1;}if(axis == 2){return nbytwo - nbytwo;}}
	if(part == 3){if(axis == 1){return nbytwo - nbytwo;}if(axis == 2){return nbytwo-1;}}
	if(part == 4){if(axis == 1){return nbytwo - nbytwo;}if(axis == 2){return nbytwo - nbytwo;}}
}