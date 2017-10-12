#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>
#include<limits>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS,
		no_property, property<edge_weight_t, int> > Graph;
int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n,m; cin>>n>>m;
		Graph g(4*n);
		int s,t; cin>>s>>t;
		// w:e - e:e 0
		// w:e - e:o 1
		// w:o - e:o 2
		// w:o - e:e 3
		for(int i=0; i<m; ++i){
			int a,b, w; cin>>a>>b >> w;
			if( w%2 ==0){
				add_edge(4*a,4*b+1,w,g);
				add_edge(4*a+1,4*b,w,g);
				add_edge(4*a+2,4*b+3,w,g);
				add_edge(4*a+3,4*b+2,w,g);
			}
			else{
				add_edge(4*a,4*b+2,w,g);
				add_edge(4*a+1,4*b+3,w,g);
				add_edge(4*a+2,4*b,w,g);
				add_edge(4*a+3,4*b+1,w,g);
			}
		}

		vector<int>d(4*n);
		dijkstra_shortest_paths(g, 4*s, distance_map(&d[0]));

		if(d[4*t+2] == numeric_limits<int>::max())
			cout << "no\n";
		else		
			cout << d[4*t+2] << "\n";
	}
	return 0;
}

