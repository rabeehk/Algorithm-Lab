#include <iostream>
#include <algorithm>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef	adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
	property<edge_capacity_t, long,
		property<edge_residual_capacity_t, long,
			property<edge_reverse_t, Traits::edge_descriptor> > > >	Graph;
typedef	property_map<Graph, edge_capacity_t>::type		EdgeCapacityMap;
typedef	property_map<Graph, edge_residual_capacity_t>::type	ResidualCapacityMap;
typedef	property_map<Graph, edge_reverse_t>::type		ReverseEdgeMap;
typedef	graph_traits<Graph>::vertex_descriptor			Vertex;
typedef	graph_traits<Graph>::edge_descriptor			Edge;



// Custom add_edge, also creates reverse edges with corresponding capacities.
void addEdge(int u, int v, long c, EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge, Graph &G) {
	Edge e, reverseE;
	tie(e, tuples::ignore) = add_edge(u, v, G);
	tie(reverseE, tuples::ignore) = add_edge(v, u, G);
	capacity[e] = c;
	capacity[reverseE] = 0;
	rev_edge[e] = reverseE;
	rev_edge[reverseE] = e;
}

// nice print
#include <boost/graph/graphviz.hpp>
#include <sstream>
class EdgeLW {
public:
	Graph G;
	EdgeLW(const Graph &G) : G(G) {}
	void operator()(std::ostream& out, const Edge& e) {
		EdgeCapacityMap capacity = get(edge_capacity, G);
		stringstream ss;
		ss << " " << (capacity[e] - get(edge_residual_capacity, G)[e])
			<< "/" << capacity[e];
		if (capacity[e] > 0) out << "[label=\"" << ss.str() << "\"]";
		else  out << "[color=none]";
	}
};

int main() {
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n,m; cin>>n>>m;
		// Create Graph and Maps
		Graph G(n+2);
		int sink = n+1;
		int source = n;

		EdgeCapacityMap	capacity = get(edge_capacity, G);
		ReverseEdgeMap	rev_edge = get(edge_reverse, G);
		ResidualCapacityMap	res_capacity = get(edge_residual_capacity, G);

		int sumg =0, sumd =0;
		for(int i=0; i<n; ++i){
			int g,d; cin>>g>>d; // exists, need
			addEdge(source, i, g, capacity, rev_edge, G);
			addEdge(i, sink, d, capacity, rev_edge, G);
			sumd += d;
			sumg+=g;
		}
		bool done = false;
		if(sumg < sumd)
			done = true;

		int flowd = sumd;
		for(int i=0; i<m; ++i){
			int a,b,cmin,cmax; cin >> a >>b>>cmin>>cmax;
			addEdge(a, b, cmax-cmin, capacity, rev_edge, G);
			if(cmin > 0){
				addEdge(a, sink, cmin, capacity, rev_edge, G);
				addEdge(source, b, cmin, capacity, rev_edge, G);
				flowd+=cmin;
			}
		}

		if(done)
			{cout << "no\n";continue;}


		// Calculate flow
		long flow = push_relabel_max_flow(G, source, sink);

		if(flow == flowd)
			cout << "yes\n";
		else
			cout << "no\n";


ofstream ofs;
ofs.open("tmp.dot");
write_graphviz(ofs, G,
	make_label_writer(get(vertex_index, G)),
	EdgeLW(G));
dot -Tpng tmp.dot > tmp.png
evince tmp.png


	}
	return 0;
}

