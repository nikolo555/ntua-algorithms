//==================================
// Author: Papadopoulos Nikolas   
// Date: 25 November 2018         
// Course: Algorithms, ECE NTUA
// Title: lab01, poleodomia 
//==================================
#include <stdio.h>
#include <iostream>
#include <utility>
#include <stack>
#include <fstream>

using namespace std;

int main(int argc, char **argv){

	std::ios::sync_with_stdio(false);

	//============== Reading Input from file ===============
	ifstream fin; // Define and Open the file
	fin.open(argv[1]);

	long long int N;
	fin >> N; //Variable of first line

	long long int* heights = new long long int[N];
	for(long long int i = 0; i < N; i++){
		fin >> heights[i];
	}
	fin.close(); // Close the file 
	//======================================================

	stack <long long int> sta, sta2, temp_stack;
	long long int tempIdx;
	long long int* first_greater_left = new long long int[N];
	long long int* first_greater_right = new long long int[N];
	long long int* costLeft = new long long int[N];
	long long int* costRight = new long long int[N];

	sta.push(0);
	first_greater_left[0] = 0;
    for(long long int i=1; i<N; i++){
    	while(! sta.empty() && heights[sta.top()] <= heights[i]){
    		sta.pop();
    	}
    	sta.push(i);
    	if(sta.size() == 1){
    		first_greater_left[i] = sta.top();
    	}
    	else{
    		temp_stack = sta;
    		temp_stack.pop();
    		first_greater_left[i] = temp_stack.top();
    	}	
    }

    sta2.push(N-1);
	first_greater_right[N-1] = N-1;
    for(long long int i=N-1; i>=0; i--){
    	while(! sta2.empty() && heights[sta2.top()] <= heights[i]){
    		sta2.pop();
    	}
    	sta2.push(i);
    	if(sta2.size() == 1){
    		first_greater_right[i] = sta2.top();
    	}
    	else{
    		temp_stack = sta2;
    		temp_stack.pop();
    		first_greater_right[i] = temp_stack.top();
    	}	
    }


    costLeft[0] = heights[0];

    for(long long int i=1; i<N; i++){
    	tempIdx = first_greater_left[i];
    	if (i == tempIdx){
    		costLeft[i] = (i+1) * heights[i];
    	}
    	else{
    		costLeft[i] = costLeft[tempIdx] + (i - tempIdx) * heights[i];
    	}
    }

    costRight[N-1] = heights[N-1];

    for(long long int i=N-1; i>=0; i--){
    	tempIdx = first_greater_right[i];
    	if (i == tempIdx){
    		costRight[i] = (N-i) * heights[i];
    	}
    	else{
    		costRight[i] = costRight[tempIdx] + (tempIdx - i) * heights[i];
    	}
    }

    long long int min, temp;
    min = costLeft[0] + costRight[0] - heights[0];
    for(long long int i=0; i<N; i++){
    	temp = costLeft[i] + costRight[i] - heights[i];
    	if( min > temp){
    		min = temp;
    	}
    }

    // freed the allocated memory 
    delete heights; 
    delete first_greater_left; 
    delete first_greater_right;
    delete costLeft; 
    delete costRight;

    cout<<min<<endl;

	return 0;
}


