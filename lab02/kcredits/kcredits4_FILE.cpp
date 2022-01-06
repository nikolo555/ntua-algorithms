//==================================
// Author: Papadopoulos Nikolas   
// Date: 28 December 2019        
// Course: Algorithms, ECE NTUA
// Title: lab02, kcredits 
// LIS with k exceptions
// O(kn^2), DP Solution
//==================================

#include <stdio.h>
#include <iostream>
#include <utility>
#include <stack>
#include <fstream>
#include <cmath>

using namespace std;

int main(int argc, char **argv)
{
    //============== Reading Input from file ===============
    long long int N, K;

    ifstream fin; // Define and Open the file
    fin.open(argv[1]);
    fin >> N >> K; //2 variables of first line

    long long int value1, credits[N];
    for(long long int i = 0; i < N; i++){
        fin >> value1;
        credits[i] = value1;
    }
    
    fin.close(); // Close the file 
    //======================================================

    long long int klis[K+1][N], lis[N];
    
    lis[0] = 1;    
  
    // Compute optimized LIS values in bottom up manner 
    // every position of lis array stands for LIS value ending 
    // in arr[i]
    for (long long int i = 1; i < N; i++ )  
    { 
        lis[i] = 1; 
        for (long long int j = 0; j < i; j++ )   
            if ( credits[i] > credits[j] && lis[i] < lis[j] + 1)  
                lis[i] = lis[j] + 1;  
    }

    // Compute newlis[] where every position of lis array 
    // stands for LIS value ending in arr[i] 
    long long int max1 = lis[0];
    klis[0][0] = max1;
    for (long long int i = 1; i < N; i++ )  
    { 
        if(lis[i] > max1){
            max1 = lis[i];
        }
        klis[0][i] = max1; 
    } 

    
    long long int max_length;
    // Fill the klis[][] array
    for(long long int k = 1; k <= K; k++){
        klis[k][0] = 1;
        for(long long int n = 1; n < N; n++){
            //find the max value of LIS for all points less than i,
            //which are not exception points
            max_length = klis[k][0];
            for (long long int j = 0; j < n; j++){
                if(credits[n] > credits[j]){
                    max_length = max(max_length, klis[k][j] + 1);
                }
                else{
                    max_length = max(max_length, klis[k-1][j] + 1) ;
                }
                //cout<<"max_length "<<n<<" ==> "<<j<<": "<<max_length<<endl;
            }
            klis[k][n] = max_length;
        }
    }

    //find maximum for k exceptions
    long long int max = klis[K][0];
    for(int i = 1; i < N; i++){
        if(klis[K][i] > max){
            max = klis[K][i];
        }
    }

    cout<<max<<endl;

    return 0;
}


