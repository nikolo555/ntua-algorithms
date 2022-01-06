//==================================
// Author: Papadopoulos Nikolas   
// Date: 26 January 2020        
// Course: Algorithms, ECE NTUA
// Title: lab03, distances
//
// References:
// https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/
//==================================


// C++ program for Kruskal's algorithm to find Minimum Spanning Tree 
// of a given connected, undirected and weighted graph 
#include <bits/stdc++.h> 
using namespace std; 

// a structure to represent a weighted edge in graph 
class Edge 
{ 
	public: 
	int src, dest, weight; 
}; 

// a structure to represent a connected, undirected 
// and weighted graph 
class Graph 
{ 
	public: 
	// V-> Number of vertices, E-> Number of edges 
	int V, E; 

	// graph is represented as an array of edges. 
	// Since the graph is undirected, the edge 
	// from src to dest is also edge from dest 
	// to src. Both are counted as 1 edge here. 
	Edge* edge; 
}; 

// Creates a graph with V vertices and E edges 
Graph* createGraph(int V, int E) 
{ 
	Graph* graph = new Graph; 
	graph->V = V; 
	graph->E = E; 

	graph->edge = new Edge[E]; 

	return graph; 
} 

// A structure to represent a subset for union-find 
class subset 
{ 
	public: 
	int parent; 
	int rank; 
}; 

// A utility function to find set of an element i 
// (uses path compression technique) 
int find(subset subsets[], int i) 
{ 
	// find root and make root as parent of i 
	// (path compression) 
	if (subsets[i].parent != i) 
		subsets[i].parent = find(subsets, subsets[i].parent); 

	return subsets[i].parent; 
} 

// A function that does union of two sets of x and y 
// (uses union by rank) 
void Union(subset subsets[], int x, int y) 
{ 
	int xroot = find(subsets, x); 
	int yroot = find(subsets, y); 

	// Attach smaller rank tree under root of high 
	// rank tree (Union by Rank) 
	if (subsets[xroot].rank < subsets[yroot].rank) 
		subsets[xroot].parent = yroot; 
	else if (subsets[xroot].rank > subsets[yroot].rank) 
		subsets[yroot].parent = xroot; 

	// If ranks are same, then make one as root and 
	// increment its rank by one 
	else
	{ 
		subsets[yroot].parent = xroot; 
		subsets[xroot].rank++; 
	} 
} 

// Compare two edges according to their weights. 
// Used in qsort() for sorting an array of edges 
int myComp(const void* a, const void* b) 
{ 
	Edge* a1 = (Edge*)a; 
	Edge* b1 = (Edge*)b; 
	return a1->weight > b1->weight; 
} 

// The main function to construct MST using Kruskal's algorithm 
// returns a vector of pait that represents an adjancy list for 
// the MST
void KruskalMST(Graph* graph, vector< pair<int,int> > g[]) 
{ 
	int V = graph->V; 
	Edge result[V]; // Tis will store the resultant MST 
	int e = 0; // An index variable, used for result[] 
	int i = 0; // An index variable, used for sorted edges 

	// Step 1: Sort all the edges in non-decreasing 
	// order of their weight. If we are not allowed to 
	// change the given graph, we can create a copy of 
	// array of edges 
	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp); 

	// Allocate memory for creating V ssubsets 
	subset *subsets = new subset[( V * sizeof(subset) )]; 

	// Create V subsets with single elements 
	for (int v = 0; v < V; ++v) 
	{ 
		subsets[v].parent = v; 
		subsets[v].rank = 0; 
	} 

	// Number of edges to be taken is equal to V-1 
	while (e < V - 1 && i < graph->E) 
	{ 
		// Step 2: Pick the smallest edge. And increment 
		// the index for next iteration 
		Edge next_edge = graph->edge[i++]; 

		int x = find(subsets, next_edge.src); 
		int y = find(subsets, next_edge.dest); 

		// If including this edge does't cause cycle, 
		// include it in result and increment the index 
		// of result for next edge 
		if (x != y) 
		{ 
			result[e++] = next_edge; 
			Union(subsets, x, y); 
		} 
		// Else discard the next_edge 
	} 

	// print the contents of result[] to display the 
	// built MST 
	//cout<<"Following are the edges in the constructed MST\n"; 
	for (i = 0; i < e; ++i){
        int a, b, c;
        a = result[i].src;
        b = result[i].dest;
        c = result[i].weight;

        g[a].push_back(make_pair(b,c));
        g[b].push_back(make_pair(a,c)); 
    } 
	 
	return; 
} 

void dfs(int node, int cost, int parent, int N, vector< pair<int,int> > g[], int subsize[], long long int binaryTimes[])
{
    subsize[node] = 1; //subsize of each node starts with one
    
    for(auto it:g[node])
    {
        int next = it.first;
        int c = it.second;
        if(next != parent)
        {
            dfs(next, c, node, N, g, subsize, binaryTimes);
            subsize[node] += subsize[next]; //subsize[node]+=(subsize[of all of it's child node])
        }
        if(cost > -1){
            binaryTimes[cost] = (long long)subsize[node] * (long long)(N - subsize[node]);
        }
		
    }
	//if(cost == 0) cout<<"WOOOOW - "<<subsize[node]<<" - "<<N - subsize[node]<<endl;
    
    //res = res + (long long)subsize[node] * (long long)(N - subsize[node]) * (long long)cost;
}



// Driver code 
int main(int argc, char **argv) 
{ 
    //============== Reading Input from file ===============
    int N, M;

    ifstream fin; // Define and Open the file
    fin.open(argv[1]);
    fin >> N >> M; //2 variables of first line

    struct Graph* graph = createGraph(N, M); 

    int x, y, z;
    for(int i = 0; i < M; i++){
        fin >> x >> y >> z;
        graph->edge[i].src = x-1; 
	    graph->edge[i].dest = y-1; 
        graph->edge[i].weight = z;
    }

    

    fin.close(); // Close the file 
    //======================================================

    //the MST's adjacent list
    //pair.first=node,pair.second-cost
    vector< pair<int,int> > g[N]; 

    int subsize[N]; //subsize[N] contains subsize of each node in dfs tree

    //Define and initilize array to represent final sum
	long long int binaryTimes[M];
	for(int i = 0; i < M; i++){
		binaryTimes[i] = 0;
	}

	KruskalMST(graph, g); 

    int root = 0;
    dfs(root, -1, -1, N, g, subsize, binaryTimes);

    //find which is the largest index in binaryTimes not equal to 0
	int largestIndex = 0;
	for(int i = M - 1; i >= 0; i--){
		if(binaryTimes[i] != 0){
			largestIndex = i;
			break;
		}
	}



    for(int z = 1; z < N+1; z++)
        g[z].clear();

    // vector to store binary number
    vector<int> binaryNum;

	for(int i = 0; i < largestIndex; i++){
		if(binaryTimes[i] % 2 == 0) binaryNum.push_back(0); 
		else binaryNum.push_back(1);

		binaryTimes[i+1] = binaryTimes[i+1] + (binaryTimes[i] / 2);
	}
    if(binaryTimes[largestIndex] % 2 == 0) binaryNum.push_back(0); 
	else binaryNum.push_back(1);


    long long int temp = binaryTimes[largestIndex];
    while(temp > 0){
		temp = temp / 2;
		if(temp == 0) break;
        if(temp % 2 == 0) binaryNum.push_back(0);
        else binaryNum.push_back(1);
    }
	
    for (auto i = binaryNum.end()-1; i >= binaryNum.begin(); --i) 
		cout << *i; 


	cout<<endl;

	return 0; 
} 

