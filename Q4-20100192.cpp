#include <iostream>
using namespace std;
				
				
				/* Before modification, complexity was O(n*n*n)
				 * Now the complexity is O(n*n) -> upper bound
				 * and O(n*n) ->lower bound
				 */

				/********************* Q4-i **********************
				 *	The time complexity is O(logn).
				 *	i starts from 1 and goes to n. But it gets 
				 *	doubled at each iteration. So suppose for 
				 *	n = 10, at first i was 1, then at next iteration
				 *	i*2 = 2, then 4 and it goes like this:
				 *	1 -> 2 -> 4 -> 8 ||STOP
				 *	This way total iterations are approximately log(n)
				 *	So the time complexity is O(logn).
				 *************************************************/


				/****************** Q4-iia ************************ 
				 * Actually, At first iteration, func() gets called 
				 * 1 time and in next iteration, it is 2 time, and 
				 * then 3, 4 and so on until y gets to n. Then in 
				 * next iteration, it starts from 2 times then 3 
				 * times and so on. The trend of iterations becomes:
				 * 		1+2+3+.....n
				 * 		  2+3+.....n
				 * 		    3+.....n
				 * 		    	.
				 * 		    	.
				 * 		    	.
				 * 		       n-1 n
				 * 		           n
				 *
				 * It can be written as 
				 * (1^2)+(2^2)+(3^2)+.....(n^2)
				 * which is equal to (n)(n+1)(2n+1)/6
				 * i.e O(n^3).
				 ****************************************************/


				/******************* Q4-iib   ************************
				 *	in 2D W array, at each cell W[x][y] the sum of 
				 *	elemenst of P from index x to y is being stored
				 *  And only the cells in upper side of diagonal 
				 *  are being populated.
				 *****************************************************/


				/*
					After modification, func becomes constant time,
					so the trends of iteration also changes and it
					becomes (n-1)+(n-2)+(n-3)+.....+1 so it is actually 
					O(n^2).
				 */


void printW(int array[5][5], int a){
	for(int i=0; i< a; i++){
		for(int j=0; j< a; j++){
			cout<< array[i][j]<<"  ";
		}cout<<endl;
	}
}

void init_zero(int array[5][5], int a){
	for(int i=0; i< a; i++){
		for(int j=0; j< a; j++){
			array[i][j] = 0;
		}
	}
}

int sum(int* array,int a){
	int sum = 0;
	for(int i=0; i< a; i++){
		sum += array[i];
	}
	return sum;
}

int main(){
	int x,y,n;
	n = 5;
	int P[n] = {1,2,3,4,5};
	int sum_p = sum(P,n);
	int sum_rp = sum_p;
	int W[5][5];
	init_zero(W,n);
	for(x = 0 ; x < n; x++){
		cout<<x<<":x"<<endl;
		int sum_rp_2 = sum_rp;
		for(y = n-1 ; y > x ; y--){
			cout<<sum_rp_2<<endl;
			W[x][y] = sum_rp_2;
			sum_rp_2 = sum_rp_2 - P[y];
		}
		sum_rp = sum_rp - P[x];
	}

	printW(W,n);
	return 0;
}
