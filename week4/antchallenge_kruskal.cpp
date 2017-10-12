#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/kruskal_min_spanning_tree.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>
#include<vector>
//#include <boost/tuple/tuple.hpp>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property,
		property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map<Graph, edge_weight_t>::type WeightMap;

int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int t,e,s,a,b; //node, edge, species, start, end
		cin>>t>>e>>s>>a>>b;

		vector<Graph>gs(s, Graph(t));
		vector<WeightMap> wms(s);
		/*for(int i=0; i<s; ++i){
			wms[i]=get(edge_weight, gs[i]);
		}*/

		bool added;
		Edge e1;
		for(int i=0; i<e; ++i){
			int u,v; cin>>u>>v;
			for(int j=0; j<s; ++j){
				int w; cin>>w; //weight
				tie(e1, added)=add_edge(u, v, gs[j]);
				wms[j][e1]=w;
			}
		}

		vector<int>hs(s);
		for(int i=0; i<s; ++i)
			cin>>hs[i];

		//build minimum spanning tree for each species
		// build the final graph
		Graph g(t);
		WeightMap wm;
		//wm=get(edge_weight, g);
		for(int i=0; i<s; ++i){
			vector<Edge> mst;
			kruskal_minimum_spanning_tree(gs[i], back_inserter(mst));
			vector<Edge>::iterator ebeg,eend=mst.end();
			for(ebeg=mst.begin(); ebeg!=eend; ++ebeg){
				int u = source(*ebeg, gs[i]);
				int v = target(*ebeg, gs[i]);
				tie(e1, added)=add_edge(u,v,g);
				wm[e1]=wms[i][*ebeg];
			}
		}

		vector<int>ds(t);
		dijkstra_shortest_paths(g, a, distance_map(&ds[0]));
		cout << ds[b] << "\n";
	}
	return 0;
}

