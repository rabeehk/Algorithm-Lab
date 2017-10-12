#include <boost/graph/biconnected_components.hpp>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <iostream>
#include<algorithm>

using namespace std;
using namespace boost;

struct edge_component_t
{
	enum
	{ num = 555 };
	typedef edge_property_tag kind;
}edge_component;

typedef adjacency_list < vecS, vecS, undirectedS,
		no_property, property < edge_component_t, std::size_t > > Graph;

typedef graph_traits<Graph>::edge_iterator EdgeIterator;
typedef graph_traits<Graph>::edge_descriptor Edge;

int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n,m; cin>>n>>m;
		Graph g(n);
		for(int i=0; i<m; ++i){
			int a,b; cin>>a>>b;
			a--;b--;
			add_edge(a,b,g);
		}
		property_map < Graph, edge_component_t >::type
		component = get(edge_component, g);

		int num_comps = biconnected_components(g, component);



		vector<int> num(num_comps, 0);
		EdgeIterator ei, ei_end;
		for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei){
			num[component[*ei]]++;
		}

		vector<pair<int,int> > bridges;
		for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei){
			int u = source(*ei, g);
			int v = target(*ei, g);
			if(num[component[*ei]] == 1){
				bridges.push_back(make_pair(min(u,v), max(u,v)));
			}
		}

		sort(bridges.begin(), bridges.end());
		cout << bridges.size() << endl;
		for(int i=0; i < bridges.size(); ++i){
			cout << bridges[i].first+1 << " " << bridges[i].second+1 << endl;
		}
	}
	return 0;
}

