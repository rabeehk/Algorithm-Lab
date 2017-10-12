//============================================================================
// Name        : monkey.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<vector>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/strong_components.hpp>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS> Graph;
typedef graph_traits<Graph>::edge_iterator EdgeIterator;

int main() {
		int T; cin>> T;
	for(int tt=0; tt< T; ++tt){
		int n,m;cin>>n>>m;
		Graph g(n);
		for(int i=0; i <m; ++i){
			int a,b; cin>>a>>b; a--; b--;
			add_edge(a,b,g);
		}
		vector<int> cost(n);
		for(int i=0; i <n; ++i)
			cin >> cost[i];

		vector<int> scc(n);
		int nscc = strong_components(g, &scc[0]);

		//in edges
		vector<int>inedge(nscc, 0);
		EdgeIterator ebeg, eend;
		for(tie(ebeg, eend)=edges(g); ebeg !=eend; ++ebeg){
			int u = source(*ebeg, g);
			int v = target(*ebeg, g);
			if(scc[u] != scc[v]){
				inedge[scc[v]]++;
			}
		}


		vector<int> mini(nscc, numeric_limits<int>::max());
		for(int i=0; i < n; ++i)
			if(inedge[scc[i]] == 0)
				mini[scc[i]]= min(mini[scc[i]], cost[i]);

		int sum = 0 ;
		for(int i=0; i <nscc; ++i)
			if(inedge[i] == 0 )
				sum += mini[i];

		cout << sum << endl;



	}

		return 0;
}

