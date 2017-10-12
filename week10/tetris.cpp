#include <iostream>
#include <algorithm>
#include <vector>
#include<limits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
 
using namespace std;
using namespace boost;
 
typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
    property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long,
            property<edge_reverse_t, Traits::edge_descriptor> > > >  Graph;
typedef property_map<Graph, edge_capacity_t>::type        EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type   ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type     ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor            Vertex;
typedef graph_traits<Graph>::edge_descriptor          Edge;
 
 
 
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
 
 
int main() {
    int T; cin>>T;
    for(int tt=0; tt<T; ++tt){
        int w,n; cin>>w>>n;
 
        Graph G((w+1)*2+2); //vertex capacities
        EdgeCapacityMap capacity = get(edge_capacity, G);
        ReverseEdgeMap  rev_edge = get(edge_reverse, G);
        ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);
 
        int source = (w+1)*2;
        int sink = (w+1)*2+1;
 
        for(int i=1; i<w; ++i){
            addEdge(i, i+(w+1), 1, capacity, rev_edge, G);
        }
        int maxc = numeric_limits<int>::max();
        addEdge(0, 0+(w+1), maxc, capacity, rev_edge, G);
        addEdge((w), w+(w+1), maxc, capacity, rev_edge, G);
 
        //source and sink edges
        addEdge(source, 0, maxc, capacity, rev_edge, G);
        addEdge(w+(w+1), sink, maxc, capacity, rev_edge, G);
 
        for(int i=0; i<n; ++i){
            int a,b; cin>>a>>b;
	    if(a > b) swap(a,b);
            addEdge(a+(w+1), b, 1, capacity, rev_edge, G);
        }
 
        //number of disjoint pathese
        long flow = edmonds_karp_max_flow(G, source, sink);
        cout << flow << "\n";
 
    }
    return 0;
}
