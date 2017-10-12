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
		//if(tt == 15)
		//cout << n << " " << m << endl; 	
		Graph g(n);
		Graph gt(n);
		int s,t; cin>>s>>t; 
		//if(tt == 15)
		//	cout << s << " " << t << endl;
		s--; t--;
		for(int i=0; i<m; ++i){
			int a,b; cin>>a>>b;
			
		//	if(tt == 15)
		//	cout << a << " " << b << endl;
			 a--; b--;
			add_edge(a,b,1, g);
			add_edge(b, a, 1, gt);
		}
		//cout << "\nend\n";
		int maxm= numeric_limits<int>::max();
		int mind= maxm;
		// g
		vector<int>ds(n);
		vector<int>p(n);
		dijkstra_shortest_paths(g, s, predecessor_map(&p[0]).distance_map(&ds[0]));
		// gt
		vector<int>dst(n);
		vector<int>pt(n);
		dijkstra_shortest_paths(gt, t, predecessor_map(&pt[0]).distance_map(&dst[0]));
		if(ds[t] == maxm){cout << "no\n"; continue;}

		int cur = t;
		OutEdgeIterator eit, eend;
		while(cur != s){
			for(tie(eit, eend)=out_edges(cur, g); eit!= eend; ++eit){
				int v = target(*eit, g);
				if(v != cur && v == pt[cur]) continue;
				if(dst[v] == maxm) continue;
				int len = ds[cur]+1+dst[v];
				mind =min(mind, len);
			}
			cur = p[cur];
		}
		// for source
		cur = s;
		for(tie(eit, eend)=out_edges(cur, g); eit!= eend; ++eit){
			int v = target(*eit, g);
			// v!= cur is for the following testcase
			/*
			1
			1 1 
			1 1
			1 1 	
			*/
			if(v!= cur && v == pt[cur]) { continue;}
			if(dst[v] == maxm){ continue;}
			int len = ds[cur]+1+dst[v];
			mind =min(mind, len);
		}

		if(mind == maxm){
			cout << "no\n"; 
		}else
			cout << mind << "\n";
	}
	return 0;
}

