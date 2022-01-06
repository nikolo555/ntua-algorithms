#include <stdio.h>
#include <iostream>
#include <utility>
#include <fstream>
#include <bits/stdc++.h> //for sort()

using namespace std;

int N, K, D, T, Ts, Cs, Tf, Cf;

void solve_linEq_2_var(int a1, int b1, int c1, int a2, int b2, int c2, int& res1, int& res2){
	res1 = (b1*c2 - b2*c1) / (a1*b2 - a2*b1);
	res2 = (c1*a2 - c2*a1) / (a1*b2 - a2*b1);
}


bool is_time_valid(int capacity, int dist[]){
	int station_distance;
	int x, y;
	double total_time;
	bool flag;

	total_time = 0;
	flag = true;

	for(int i = 0; i < K+1; i++){
		station_distance = dist[i+1] - dist[i];

		double maxDistance = (double) capacity / Cs;
		if (maxDistance < station_distance){
			return false;
		}

		solve_linEq_2_var(Cs, Cf, (-1)*capacity, 1, 1, (-1)*station_distance, x, y);

		if (x < 0){
			x = 0;
			y = station_distance;
		}

		total_time = total_time + x*Ts + y*Tf;
	}
	

	if (flag && total_time <= T){
		return true;
	}
	else return false;
}


// A recursive binary search function. It returns 
// location of x in given array arr[l..r] is present, 
// otherwise -1 
int binarySearch(int left, int right, pair<int, int> capacity_n_price[], int dist[]){ 
    //=========== array with one element =============
    if (right == left){//array with one element
    	if(is_time_valid(capacity_n_price[right].first, dist)){
    		return right;
    	}
    	else return -1;
    }
    //======== array with more than one element ======
    else if (right >= left){ //array with more than one element
        int mid = (left + right) / 2; 
  		
  		//when we reach the last 2 elements
  		if(mid == left){ 

  			if(  !(is_time_valid(capacity_n_price[mid].first, dist)) && is_time_valid(capacity_n_price[mid+1].first, dist)){
  				return mid+1;
  			}
  			else{
  				return -1;
  			}
  			
  		}

        // If element in the middle is valid, then 
        // it can only be present in left subarray 
        if (is_time_valid(capacity_n_price[mid].first, dist)){
            return binarySearch(left, mid, capacity_n_price, dist); 
        }
  
        // Else if the element in the middle is NOT valid, then
        // it can only be present in right subarray 
        if (!is_time_valid(capacity_n_price[mid].first, dist)){
        	return binarySearch(mid, right, capacity_n_price, dist); 
    	}
    } 
  
    // We reach here when element is not 
    // present in array 
    return -1; 
} 





int main(int argc, char **argv){
	//============== Reading Input from file ===============
	ifstream fin; // Define and Open the file
	fin.open(argv[1]);
	fin >> N >> K >> D >> T; //4 variables of first line

	pair<int, int> capacity_n_price[N], aPair;
	int value1, value2, dist[K+2];
	for(int i = 0; i < N; i++){
		fin >> value1 >> value2;
		aPair = make_pair(value2, value1);
		capacity_n_price[i] = aPair;
	}
	dist[0] = 0; 
	dist[K+1] = D;
	for(int i = 1; i < K+1; i++){
		fin >> dist[i];
	}
	fin >> Ts >> Cs >> Tf >> Cf;
    fin.close(); // Close the file 
	//======================================================


    //Sort dist[] array
	int n = sizeof(dist)/sizeof(dist[0]);
	sort(dist, dist+n);

	//Sort capacity_n_price[] array according to capacity
	n = sizeof(capacity_n_price)/sizeof(capacity_n_price[0]);
	sort(capacity_n_price, capacity_n_price+n);


	int first_valid, minimum_cost, current_cost;

	//check if 1st element is valid. Consequently, all are valid
	if(is_time_valid(capacity_n_price[0].first, dist)){
		first_valid = 0;
	}
	else{
		first_valid  = binarySearch(0, N-1, capacity_n_price, dist);
	}

	

	if(first_valid == -1){
		cout<<-1<<endl;
		return 0;
	}
	else{
		minimum_cost = capacity_n_price[first_valid].second;
		for(int i = first_valid; i < N; i++){
			current_cost = capacity_n_price[i].second;
			if(current_cost < minimum_cost){
				minimum_cost = current_cost;
			}
		}

		cout << minimum_cost << endl;
		
		return 0;
	}
}


