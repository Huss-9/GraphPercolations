#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<list>
#include<vector>
#include <stdio.h>
#include <time.h>
#include <math.h> 
using namespace std;

#define Graph vector<list<int>>

void dfs(int v, vector<bool> &vis, const Graph graph) {
	vis[v] = true;
	for(list<int>::const_iterator it = graph[v].begin(); it != graph[v].end(); ++it) {
		if(*it!=-1 and not vis[*it]) dfs(*it, vis, graph);
	}
}

int numberOfCC(const Graph& graph) {
	int n_cc = 0;
	vector<bool> vis(graph.size(), false);
	for(int i = 0; i < graph.size(); ++i) {
		if(not vis[i]) {
			dfs(i, vis, graph);
			if(*graph[i].begin() != -1 ) ++n_cc;
		}
	}
	return n_cc;
}

void addEdge(Graph& g, int u, int v){
    g[u].push_back(v);
    g[v].push_back(u);
}

Graph createRandomGraph(int n){
	Graph g;
    g.resize(n);
    for(int i = 0; i < n; ++i){
    	for(int j = i+1; j < n; ++j){
    		if(rand()%2 == 0) addEdge(g,i,j);
		}
	}
	return g;
}

Graph createCompleteGraph(int n){
	Graph g; 
    g.resize(n);
    for(int i = 0; i < n; ++i){
    	for(int j = 0; j < n; ++j){
    		if(i != j) g[i].push_back(j);
		}
	}
	return g;
}

Graph createSquareGridGraph(int n) {
	Graph g;
	g.resize(n*n);
	int x;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			x = n*i + j; 
			 if (i < n-1 and j < n-1) {
				g[x].push_back(x + 1);
				g[x + 1].push_back(x);
				g[x].push_back(x + n);
				g[x + n].push_back(x);
			 }
			 else {
				 if (i == n-1 and j < n-1) {
					g[x].push_back(x + 1);
					g[x + 1].push_back(x);
				 }
				 else if (i < n-1 and j == n-1) {
					g[x].push_back(x + n);
					g[x + n].push_back(x);
				 }
			 }
		}
	}
	return g;
}

Graph createCubeGridGraph(int n) {
	Graph g;
	g.resize(n*n*n);
	int x;
	int y = n*n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				x = n*i + j + k*y; 
				if (i < n-1 and j < n-1 and k < n-1) {
					g[x].push_back(x + 1);
					g[x + 1].push_back(x);
					g[x].push_back(x + n);
					g[x + n].push_back(x);
					g[x].push_back(x + y);
					g[x + y].push_back(x);
				}
				else {
					if (i == n-1 and j < n-1 and k < n-1) {
						g[x].push_back(x + y);
						g[x + y].push_back(x);
						g[x].push_back(x + 1);
						g[x + 1].push_back(x);
					}
					else if (i < n-1 and j == n-1 and k < n-1) {
						g[x].push_back(x + n);
						g[x + n].push_back(x);
						g[x].push_back(x + y);
						g[x + y].push_back(x);
					}
					else if (i < n-1 and j < n-1 and k == n-1) {
						g[x].push_back(x + 1);
						g[x + 1].push_back(x);
						g[x].push_back(x + n);
						g[x + n].push_back(x);
					}
					else if (i == n-1 and j == n-1 and k < n-1) {
						g[x].push_back(x + y);
						g[x + y].push_back(x);
					}
					else if (i < n-1 and j == n-1 and k == n-1) {
						g[x].push_back(x + n);
						g[x + n].push_back(x);
					}
					else if (i == n-1 and j < n-1 and k == n-1) {
						g[x].push_back(x + 1);
						g[x + 1].push_back(x);
					}
				}
			}
		}
	}
	return g;
}

Graph createTriangularGridGraph(int n){
	Graph g;
	int N = (n+1)*(n+2)/2;
	g.resize(N); 
	int nodoTratar = 1; 
	int nodoActual = 0; 
	int nivelActual = 1; 
	while (nodoActual!=N-1){
		int x = nodoTratar; 
		while (nodoActual!=N-1 && x!=0){
			if (nodoActual+nivelActual<N) addEdge (g, nodoActual, nodoActual+nivelActual); 
			if (nodoActual+nivelActual+1<N )addEdge (g, nodoActual, nodoActual+nivelActual+1); 
			if (x>1 && nodoActual+1<N) addEdge (g, nodoActual, nodoActual+1); 
			--x; 
			++nodoActual;
		}
		++nodoTratar; 
		++nivelActual;
	}
	return g; 
}

double distance(pair<double, double> p1, pair<double, double> p2) {
	return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

void setEdgesByDistance(Graph& g, double r, const vector< pair<double, double> >& coords){
	for(int i=0; i<g.size(); ++i){
		for(int j=i+1; j<g.size(); ++j){
			double dist = distance(coords[i], coords[j]);
			if(dist <= r) addEdge(g,i,j);
		}
	}
}

Graph auxiliarRandomGeometricGraph(int n, double r, vector< pair<double, double> >& coords){
	Graph g(n);
	coords.resize(n);
	for(int i=0; i<n; ++i) {
		double x = rand()/(RAND_MAX+1.0);
		double y = rand()/(RAND_MAX+1.0);
		coords[i].first = x;
		coords[i].second = y;
	}
	setEdgesByDistance(g,r,coords);
	return g;
}

Graph createRandomGeometricGraph(int n, double r) {
	vector< pair<double, double> > coords;
	return auxiliarRandomGeometricGraph(n,r,coords);
}

void printGraph(const Graph& g){
	cout << "Printing Graph" << endl;
	for(int i = 0; i < g.size(); ++i){
		cout << i << "->";
		for(list<int>::const_iterator it = (g[i]).begin(); it != (g[i]).end(); ++it){
			if(*it == -1) cout << " This node was deleted";
			else cout << " " << *it;
		}
		if((g[i]).begin() == (g[i]).end()) cout << " Disconnected";
		cout << endl;
	}
	cout << endl;
}

void deleteNode(Graph& g, int k){
	if(k >= g.size() or *(g[k].begin()) == -1) return;
	for(list<int>::iterator it = (g[k]).begin(); it != (g[k]).end(); ++it){
		list<int>::iterator it2 = find(g[*it].begin(),g[*it].end(),k);
		g[*it].erase(it2);
	}
	g[k].erase(g[k].begin(), g[k].end());
	g[k].insert(g[k].begin(), -1);
}

void failedNodesGraph(Graph& g, double p){
	for (int i = 0; i<g.size(); ++i){
		if (rand()/(RAND_MAX+1.0) <= p){ 
			deleteNode(g, i); 
		}
	}
}

void deleteEdge(Graph& g, int u, int v){
	list<int>::iterator it = find(g[u].begin(),g[u].end(), v);
	if (it == g[u].end() ) return; 
	(g[u]).erase(it);
	list<int>::iterator it2 = find(g[v].begin(),g[v].end(),u);
	if (it2 == g[u].end() ) return; 
	(g[v]).erase(it2);
}

void failedEdgesGraph(Graph& g, double p) {
	list<int>::iterator it;
	for (int i = 0; i < g.size(); ++i) {
		for (it = (g[i]).begin(); it != (g[i]).end(); ++it) {
			if (*(it)!=-1 and rand()/(RAND_MAX+1.0) <= p) {
				deleteEdge(g, i , *it);
				--it; 
			}
		}
	}
}

bool double_equals(double a, double b) //usat per problemes d'arrodoniment del double
{
    return abs(a-b) < 0.0001;
}

void testingDeletingNodesOrEdges(Graph& g, int T, bool nodes){
	if(nodes) cout <<"Graph Test Nodes: " << endl;
	else cout <<"Graph Test Edges: " << endl;
	for(double p = 0.000; p < 1.005; p += 0.005){
		double sumConexos = 0;
		for(int i = 0; i < T; ++i){
			Graph tested = g;
			if(nodes) failedNodesGraph(tested,p);
			else failedEdgesGraph(tested,p);
			if(numberOfCC(tested) <= 1) ++sumConexos;
		}
		if(double_equals(p,0.05)) p = 0.05; //usat per problemes d'arrodoniment del double
		int prob = int(p*1000)%100;
		if(prob == 0 or prob == 50) cout << p << " " << sumConexos/T << endl; //usat per dibuixar la gràfica
		else cout << " " << sumConexos/T << endl; //usat per dibuixar la gràfica
	}
	cout << endl;
}

void testingRandomGeometricGraphNodesOrEdges(int n, int T, bool nodes){
	if(nodes) cout << "Random Geometric Graph Test Nodes:" << endl;
	else cout << "Random Geometric Graph Test Edges:" << endl;
	Graph randomGeometricGraph;
	for(double r = 0; r < sqrt(2); r += 0.05){
		cout << endl << r << endl << endl;
		for(double p = 0.000; p < 1.005; p += 0.005){
			double sumConexos = 0;
			for(int i = 0; i < T; ++i){
				randomGeometricGraph = createRandomGeometricGraph(n, r);
				if(nodes) failedEdgesGraph(randomGeometricGraph,p);
				else failedNodesGraph(randomGeometricGraph,p);
				if(numberOfCC(randomGeometricGraph) <= 1) ++sumConexos;
			}
			cout << sumConexos/T << endl; //usat per dibuixar la gràfica
		}
	}
	cout << endl;
}

void testingRandomGraphNodesOrEdges(int n, int T, bool nodes){
	if(nodes) cout << "Random Graph Test Nodes:" << endl;
	else cout << "Random Graph Test Edges:" << endl;
	Graph randomGraph;
	for(double p = 0.000; p < 1.005; p += 0.005){
		double sumConexos = 0;
		for(int i = 0; i < T; ++i){
			randomGraph = createRandomGraph(n);
			if(nodes) failedNodesGraph(randomGraph,p);
			else failedEdgesGraph(randomGraph,p);
			if(numberOfCC(randomGraph) <= 1) ++sumConexos;
		}
		if(double_equals(p,0.05)) p = 0.05; //Usat per problemes d'arrodoniment del double
		int prob = int(p*1000)%100;
		if(prob == 0 or prob == 50) cout << p << " " << sumConexos/T << endl; //usat per dibuixar la gràfica
		else cout << " " << sumConexos/T << endl; //usat per dibuixar la gràfica
	}
	cout << endl;
}

void testingCCDeletingNodesOrEdges(Graph& g, int T, bool nodes){
	if(nodes) cout <<"Graph Test Nodes: " << endl;
	else cout <<"Graph Test Edges: " << endl;
	for(double p = 0.000; p < 1.005; p += 0.005){
		double sumConexos = 0;
		for(int i = 0; i < T; ++i){
			Graph tested = g;
			if(nodes) failedNodesGraph(tested,p);
			else failedEdgesGraph(tested,p);
			sumConexos += numberOfCC(tested);
		}
		if(double_equals(p,0.05)) p = 0.05; //usat per problemes d'arrodoniment del double
		int prob = int(p*1000)%100;
		if(prob == 0 or prob == 50) cout << p << " " << sumConexos/T << endl; //usat per dibuixar la gràfica
		else cout << " " << sumConexos/T << endl; //usat per dibuixar la gràfica
	}
	cout << endl << endl;
}

void testingCCRandomGeometricGraphNodesOrEdges(int n, int T, bool nodes){
	if(nodes) cout << "Random Geometric Graph Test Nodes:" << endl;
	else cout << "Random Geometric Graph Test Edges:" << endl;
	Graph randomGeometricGraph;
	for(double r = 0.0; r < sqrt(2); r += 0.05){
		cout << endl << r << endl << endl;
		for(double p = 0.000; p < 1.005; p += 0.005){
			double sumConexos = 0;
			for(int i = 0; i < T; ++i){
				randomGeometricGraph = createRandomGeometricGraph(n, r);
				if(nodes) failedNodesGraph(randomGeometricGraph,p);
				else failedEdgesGraph(randomGeometricGraph,p);
				sumConexos += numberOfCC(randomGeometricGraph);
			}
			cout << sumConexos/T << endl; //usat per dibuixar la gràfica
		}
	}
	cout << endl << endl;
}

void testingCCRandomGraphNodesOrEdges(int n, int T, bool nodes){
	if(nodes) cout << "Random Graph Test Nodes:" << endl;
	else cout << "Random Graph Test Edges:" << endl;
	Graph randomGraph;
	for(double p = 0.000; p < 1.005; p += 0.005){
		double sumConexos = 0;
		for(int i = 0; i < T; ++i){
			randomGraph = createRandomGraph(n);
			if(nodes) failedNodesGraph(randomGraph,p);
			else failedEdgesGraph(randomGraph,p);
			sumConexos += numberOfCC(randomGraph);
		}
		if(double_equals(p,0.05)) p = 0.05; //Usat per problemes d'arrodoniment del double
		int prob = int(p*1000)%100;
		if(prob == 0 or prob == 50) cout << p << " " << sumConexos/T << endl; //usat per dibuixar la gràfica
		else cout << " " << sumConexos/T << endl; //usat per dibuixar la gràfica
	}
	cout << endl << endl;
}

int main(){
	srand(time(NULL));
	
	int tests = 500; //We always use 500 tests because it's a great reasonable number to do the average
	
	int n = 20; //Numer of nodes or number of the input that creates the graph
	//Example: CubeGridGraph(10) will create a 10^3 nodes graph.
	
	cout << "--Random Graph--" << endl;
	Graph randomGraph = createRandomGraph(n);
	//testingCCRandomGraphNodesOrEdges(n, tests, true); //CC's test with percolation of nodes that uses every test a diferent randomGraph with n nodes
	//testingCCRandomGraphNodesOrEdges(n, tests, false); //CC's test with percolation of edges that uses every test a diferent randomGraph with n nodes
	//testingRandomGraphNodesOrEdges(n, tests, true); //Connectivity test with percolation of nodes that uses every test a diferent randomGraph with n nodes
	//testingRandomGraphNodesOrEdges(n, tests, false); //Connectivity test with percolation of edges that uses every test a diferent randomGraph with n nodes
	printGraph(randomGraph); 
	
	
	cout << "--Complete Graph--" << endl;
	Graph completeGraph = createCompleteGraph(n);
	//testingCCDeletingNodesOrEdges(completeGraph, tests, true); //CC's test with percolation of nodes
	//testingCCDeletingNodesOrEdges(completeGraph, tests, false); //CC's test with percolation of edges
	//testingDeletingNodesOrEdges(completeGraph, tests, true); //Connectivity test with percolation of nodes
	//testingDeletingNodesOrEdges(completeGraph, tests, false); //Connectivity test with percolation of edges
	printGraph(completeGraph);


	cout << "--Square Grid Graph--" << endl;
	Graph squareGridGraph = createSquareGridGraph(n);
	//testingCCDeletingNodesOrEdges(squareGridGraph, tests, true); //CC's test with percolation of nodes
	//testingCCDeletingNodesOrEdges(squareGridGraph, tests, false); //CC's test with percolation of edges
	//testingDeletingNodesOrEdges(squareGridGraph, tests, true); //Connectivity test with percolation of nodes
	//testingDeletingNodesOrEdges(squareGridGraph, tests, false); //Connectivity test with percolation of edges
	printGraph(squareGridGraph);
	
	
	cout << "--Cube Grid Graph--" << endl;
	Graph cubeGridGraph = createCubeGridGraph(n);
	//testingCCDeletingNodesOrEdges(cubeGridGraph, tests, true); //CC's test with percolation of nodes
	//testingCCDeletingNodesOrEdges(cubeGridGraph, tests, false); //CC's test with percolation of edges
	//testingDeletingNodesOrEdges(cubeGridGraph, tests, true); //Connectivity test with percolation of nodes
	//testingDeletingNodesOrEdges(cubeGridGraph, tests, false); //Connectivity test with percolation of edges
	printGraph(cubeGridGraph);
	
	
	cout << "--Triangular Grid Graph--" << endl;
	Graph triangularGridGraph = createTriangularGridGraph(n);
	//testingCCDeletingNodesOrEdges(triangularGridGraph, tests, true); //CC's test with percolation of nodes
	//testingCCDeletingNodesOrEdges(triangularGridGraph, tests, false); //CC's test with percolation of edges
	//testingDeletingNodesOrEdges(triangularGridGraph, tests, true); //Connectivity test with percolation of nodes
	//testingDeletingNodesOrEdges(triangularGridGraph, tests, false); //Connectivity test with percolation of edges
	printGraph(triangularGridGraph);
	
	
	cout << "--Random Geometric Graph--" << endl;
	double r = 0.3;
	Graph randomGeometricGraph = createRandomGeometricGraph(n, r);
	
	//CC's test with percolation of nodes that uses every test a diferent randomGeometricGraph with n nodes
	//Also proves every r (0.05 separation). Long execution time!
	//testingCCRandomGeometricGraphNodesOrEdges(n, tests, true); 
	
	//CC's test with percolation of edges that uses every test a diferent randomGeometricGraph with n nodes
	//Also proves every r (0.05 separation). Long execution time!
	//testingCCRandomGeometricGraphNodesOrEdges(n, tests, false);
	
	//Connectivity test with percolation of nodes that uses every test a diferent randomGeometricGraph with n nodes
	//Also proves every r (0.05 separation). Long execution time!
	//testingRandomGeometricGraphNodesOrEdges(n, tests, true); 
	
	//Connectivity test with percolation of edges that uses every test a diferent randomGeometricGraph with n nodes
	//Also proves every r (0.05 separation). Long execution time!
	//testingRandomGeometricGraphNodesOrEdges(n, tests, false); 
	
	printGraph(randomGeometricGraph);
}
