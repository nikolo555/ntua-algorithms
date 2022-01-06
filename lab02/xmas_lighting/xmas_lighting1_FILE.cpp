//==================================
// Author: Papadopoulos Nikolas   
// Date: 28 December 2019        
// Course: Algorithms, ECE NTUA
// Title: lab02, xmas_lighting 


// References:
// https://bit.ly/2ZQaE0T

//==================================
#include <stdio.h>
#include <bits/stdc++.h>
#include <iostream>
#include <utility>
#include <stack>
#include <fstream>
#include <cmath>
#include <unordered_map>
#include <vector>

using namespace std;

// A memoization based function that returns size of the minimum vertex cover. 
int vCover(unordered_map<int, vector<int>>& road_network, int node)
{ 
    // The size of minimum vertex cover is zero if tree is empty or there 
    // is only one node
    if (road_network[node].size() == 1) // there is only one node
        return 0; 
    if (road_network.empty())  // root == NULL, tree is empty
        return 0;

     
  
    // If vertex cover for this node is already evaluated, then return it 
    // to save recomputation of same subproblem again 
    if (road_network[node][0] != 0)
        return road_network[node][0]; 

    // Calculate size of vertex cover when root is part of it
    int size_incl = 0;
    for (int i = 1; i < road_network[node].size(); i++)
    {
        size_incl = size_incl + vCover(road_network, road_network[node][i]);
    }
    size_incl = size_incl + 1;

      
    // Calculate size of vertex cover when root is not part of it 
    int size_excl = 0; 
    for (int i = 1; i < road_network[node].size(); i++)
    {
        int temp = road_network[node][i];
        for (int j = 1; j < road_network[temp].size(); j++)
        {
            size_excl = size_excl + vCover(road_network, road_network[temp][j]);
        }
        size_excl = size_excl + 1;
    } 
  
    // Minimum of two values is vertex cover, store it before returning 
    if (size_excl < size_incl){
        road_network[node][0] = size_excl;
    }
    else{
        road_network[node][0] = size_incl;
    }
  
    return road_network[node][0]; 
} 



int main(int argc, char **argv)
{
    //Define road_network, which is a general tree, as an unordered map
    //key is the number of nodes
    //and value is a vector of children of a node
    //first element of each vector stands for a counter for vertex cover
    unordered_map<int, vector<int>> road_network;
    vector<int> vec; 
    int N, K, node, child;

    //============== Reading Input from file ===============
    ifstream fin; // Define and Open the file
    fin.open(argv[1]);
    fin >> N >> K; //2 variables of first line

    //Initialize tree
    for(int i = 1; i <= N; i++){
        road_network[i] = vector<int>();
        road_network[i].push_back(0); // initiliaze counter for vertex cover
    }

    for(int i = 1; i <= N-1; i++){
        fin >> node >> child;
        road_network[node].push_back(child);
    }
    
    fin.close(); // Close the file 
    //======================================================

    
    //Print tree
    for (auto& itr: road_network){ 
        // itr works as a pointer to pair<int, vector<int>> 
        // type itr->first stores the key part  and 
        // itr->second stroes the value part 
        cout << "node "<<itr.first<<": "; 
        vec = itr.second;
        for (int i = 0; i < vec.size(); i++){
            cout<<vec[i]<<" ";
        }
        cout<<endl;
     }
     

    int result;

    result = vCover(road_network, 1);

    cout<<result<<endl;

        
    return 0;
}


