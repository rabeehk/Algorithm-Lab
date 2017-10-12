#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/prim_minimum_spanning_tree.hpp>
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
		for(int i=0; i<s; ++i){
			wms[i]=get(edge_weight, gs[i]);
		}

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
		wm=get(edge_weight, g);
		Edge e2;
		for(int i=0; i<s; ++i){
			vector<int>p(t);
			prim_minimum_spanning_tree(gs[i], &p[0], root_vertex(hs[i]));
			for(int j=0; j<t; ++j){
				if(j != p[j]){
					Edge e1;
					tie(e1,added)=edge(j, p[j], gs[i]);
					tie(e2,added)=add_edge(j, p[j], g);
					wm[e2]=wms[i][e1];
				}
			}
		}

		vector<int>ds(t);
		dijkstra_shortest_paths(g, a, distance_map(&ds[0]));
		cout << ds[b] << "\n";
	}
	return 0;
}

