#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>
#include<boost/graph/kruskal_min_spanning_tree.hpp>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
		no_property, property<edge_weight_t, long> > Graph;
typedef property_map<Graph, edge_weight_t>::type WeightMap;
typedef graph_traits<Graph>::edge_descriptor Edge;

int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n; cin>>n;
		int m; cin>>m;
		Graph g(n);
		WeightMap wm=get(edge_weight, g);
		Edge e;
		bool added;
		for(int i=0; i<m; ++i){
			int a,b,c; cin>>a>>b>>c;
			tie(e, added)= add_edge(a,b,g);
			wm[e]=c;
		}

		vector<long>ds(n);
		dijkstra_shortest_paths(g, 0, distance_map(&ds[0]));
		long maxd = numeric_limits<long>::min();
		for(int i=0; i<n; ++i)
			maxd = max(maxd, ds[i]);

		vector<Edge>mst;
		kruskal_minimum_spanning_tree(g, back_inserter(mst));
		long sum=0;
		//vector<Edge>::iterator ebeg,eend=mst.end();
		//for(ebeg=mst.begin(); ebeg!=eend; ++ebeg){
		//sum += wm[*ebeg];
		//}
		for(int i=0; i<mst.size(); ++i){
			sum += wm[mst[i]];
			//cout << source(mst[i], g) << " " << target(mst[i], g) << endl;	
		}

		cout << sum << " " << maxd << "\n";
	}
	return 0;
}

