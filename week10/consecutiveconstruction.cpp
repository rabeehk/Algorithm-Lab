/*maximum matching in augmented graph*/
#include<iostream>
#include<vector>
#include<boost/graph/max_cardinality_matching.hpp>
#include<boost/graph/adjacency_list.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;

int main()
{
	int T; cin >>T;
	for(int tt=0; tt<T; ++tt){
		int n,m; cin >> n >> m;
		
		Graph g(2*n);
		for(int i=0; i <m; ++i){
			int s,t; cin >> s >> t;
			s--; t--;
			// we only want the edges which start 
			// from small number and end in bigger number
			if(s < t)
			add_edge(s,t+n,g);
		}

		//maximum matching 
		vector<int>mate(2*n);
		edmonds_maximum_cardinality_matching(g, &mate[0]);
		int size = matching_size(g, &mate[0]);
		cout << size << endl;		
	}
	return 0;
}
