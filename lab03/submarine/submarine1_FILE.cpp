//==================================
// Author: Papadopoulos Nikolas   
// Date: 25 January 2020        
// Course: Algorithms, ECE NTUA
// Title: lab03, submarine 
//==================================

#include <stdio.h>
#include <iostream>
#include <utility>
#include <stack>
#include <fstream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;


int main(int argc, char **argv)
{
    //============== Reading Input from file ===============
    int N, M, K, X;

    //create a map for storing which 
    //coordinates are pilot crossings
    //1, if pilot crossings. 0, if not.
    map<pair<int, int>, pair<int, int>> pilots;

    ifstream fin; // Define and Open the file
    fin.open(argv[1]);
    fin >> N >> M >> K >> X; //4 variables of first line

    int x, y;
    for(int i = 0; i < K; i++){
        fin >> x >> y;
        pilots[{x / M, x % M}] = {y / M, y % M};      
    }

    fin.close(); // Close the file 
    //======================================================

    long long int radar[N][M][K+1];

    //Initialize radar grid
    for(int k = 0; k <= K; k++){
        if (k == 0){
            radar[0][0][k] = 1;
        }
        else radar[0][0][k] = 0;
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            //if there is no pilot crossing in (i, j) point
            if ( pilots.find({i, j}) == pilots.end() ){
                if(i == 0){
                    if(j != 0){
                        for(int k = 0; k <= X; k++){
                            radar[i][j][k] = radar[i][j - 1][k] % 1000000103;
                        }
                    }
                }
                else if(j == 0){
                    if(i != 0){
                        for(int k = 0; k <= X; k++){
                            radar[i][j][k] = radar[i - 1][j][k] % 1000000103;
                        }
                    }
                    
                }
                else{
                    for(int k = 0; k <= X; k++){
                        radar[i][j][k] = (radar[i][j - 1][k] + radar[i - 1][j][k]) % 1000000103;
                    } 
                }  
            }
            //if there is a pilot crossing in (i, j) point
            else{ 
                radar[i][j][0] = 0;
                x = pilots[{i, j}].first;
                y = pilots[{i, j}].second;
                for(int k = 1; k <= X; k++){
                    radar[i][j][k] = radar[x][y][k - 1];
                }


            }
        }
    }

    /*
    //print final grid
    for(int i = 0; i < N; i++){
        for(int k = 0; k <= X; k++){
            for(int j = 0; j < M; j++){
                cout<<radar[i][j][k]<<"  ";
            }
            cout<<endl;
        }
        cout<<endl<<endl;
    }
    */
    
    int result = 0; 
    for(int k = 0; k <= X; k++){
        result = (result + radar[N - 1][M - 1][k])% 1000000103;
    }

    cout<<result<<endl;

    return 0;
}


