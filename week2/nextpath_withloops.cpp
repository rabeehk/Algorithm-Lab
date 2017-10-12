// removing the edges of shortest path one by one
#include<iostream>
#include<boost/graph/dijkstra_shortest_paths.hpp>
#include<boost/graph/adjacency_list.hpp>
#include<vector>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, no_property,
		property<edge_weight_t, int> > Graph;

typedef graph_traits<Graph>::out_edge_iterator OutEdgeIterator;
int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n,m; cin>>n>>m;
		Graph g(n);
		int s,t; cin>>s>>t; s--; t--;
		for(int i=0; i<m; ++i){
			int a,b; cin>>a>>b; a--; b--;
			add_edge(a,b,1, g);
		}
		vector<int>ds(n);
		vector<int>p(n);
		dijkstra_shortest_paths(g, s, predecessor_map(&p[0]).distance_map(&ds[0]));
		int maxm = numeric_limits<int>::max();
		if(ds[t] == maxm)
		{cout << "no\n"; continue;}
		//try to remove each edge of shortest path
		int cur=t;
		int mind = maxm;
		while(cur != s){
			remove_edge(p[cur], cur, g);
			vector<int> d(n);
			dijkstra_shortest_paths(g, s, distance_map(&d[0]));
			mind= min(mind, d[t]);
			add_edge(p[cur], cur, 1,  g);
			cur = p[cur];
		}


		// look for loops, find the shortest path from out edges to this node 
		// then add one also for this edge
		// as shortest distance from a node to itself is zero, we need to cut one of the edges
		cur = t;
		OutEdgeIterator eit, eend;
		while(cur != s){
			for(tie(eit, eend)=out_edges(cur, g); eit!= eend; ++eit){
				int v = target(*eit, g);
				vector<int> d(n);
				dijkstra_shortest_paths(g, v, distance_map(&d[0]));
				if(d[cur] == maxm) continue;
				int len = d[cur]+1+ds[t];
				mind = min(mind, len);
			}
			cur = p[cur];
		}
		// for source node 
		for(tie(eit, eend)=out_edges(s, g); eit!= eend; ++eit){
			int v = target(*eit, g);
			vector<int> d(n);
			dijkstra_shortest_paths(g, v, distance_map(&d[0]));
			if(d[s] == maxm) continue;
			int len = d[s]+1+ds[t];
			mind = min(mind, len);
		}

		if(mind == maxm)
			cout << "no\n";
		else
			cout << mind << "\n";
	}
	return 0;
}

