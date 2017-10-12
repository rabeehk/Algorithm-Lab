#include<iostream>
#include<boost/graph/push_relabel_max_flow.hpp>
using namespace std;
using namespace boost;
#include<boost/graph/adjacency_list.hpp>
#include<limits>

typedef
adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef
adjacency_list<vecS, vecS, directedS, no_property,
property<edge_capacity_t,
long
,
property<edge_residual_capacity_t,
long
,
property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;
typedef
property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef
property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef
property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef
graph_traits<Graph>::edge_descriptor Edge;
typedef
graph_traits<Graph>::vertex_descriptor Vertex;


void addEdge(int from, int to, long c, EdgeCapacityMap &capacity,
		ReverseEdgeMap &rev_edge, Graph &g){
	Edge e, reverseE;
	tie(e, tuples::ignore) = add_edge(from, to, g);
	tie(reverseE, tuples::ignore) = add_edge(to, from, g);
	capacity[e]=c;
	capacity[reverseE] = 0;
	rev_edge[e]=reverseE;
	rev_edge[reverseE] = e;
}


int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n,m,k,l; cin>>n>>m>>k>>l;
		Graph g(2*n+2);
		int source = 2*n;
		int sink = 2*n+1;

		EdgeCapacityMap capacity = get(edge_capacity, g);
		ReverseEdgeMap rev_edge = get(edge_reverse, g);
		ResidualCapacityMap res_capacity = get(edge_residual_capacity, g);

		for(int i=0; i <k; ++i){ //police
			int p; cin>>p;
			addEdge(source, p, 1, capacity,rev_edge, g);
			addEdge(p+n, sink, 1, capacity,rev_edge, g);
		}

		for(int i=0; i <l; ++i){ //photo
			int p; cin>>p;
			addEdge(p, p+n, 1, capacity,rev_edge, g); // take only one photo
		}

		int maxc = numeric_limits<int>::max();
		for(int i=0; i <m; ++i){
			int a,b; cin>>a>>b;
			addEdge(a, b, maxc, capacity, rev_edge, g);
			addEdge(a+n, b+n, 1, capacity, rev_edge, g);
		}

		long flow = push_relabel_max_flow(g, source, sink);
		cout << flow << endl;

	}

	return 0;
}

