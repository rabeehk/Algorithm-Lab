#include <iostream>
#include <algorithm>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
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
    ios_base::sync_with_stdio(false);
    int T; cin>>T;
    for(int tt=0; tt<T; ++tt){
        int n,m; cin>>n>>m;
        // Create Graph and Maps
        Graph G(n+m+2);
        int source = n+m;
        int sink = n+m+1;
        EdgeCapacityMap capacity = get(edge_capacity, G);
        ReverseEdgeMap  rev_edge = get(edge_reverse, G);
        ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);
 
        vector<int> reals(n, 0);
        int sums = 0;
        for(int i=0; i<m; ++i){
            int a,b,c; cin>>a>>b>>c;
            if(c==0){
                addEdge(i, a+m, 1, capacity, rev_edge, G);
                addEdge(i, b+m, 1, capacity, rev_edge, G);
            }else if(c==1){
                reals[a]++;
                addEdge(i, a+m, 1, capacity, rev_edge, G);
            }else{ //c == 2
                reals[b]++;
                addEdge(i, b+m, 1, capacity, rev_edge, G);
            }
            addEdge(source, i, 1, capacity, rev_edge, G);
        }
 
        bool done = false;
        for(int i=0; i<n; ++i){
            int s; cin>>s;
            if(reals[i] > s)
                done = true;
            sums+=s;
            addEdge(i+m, sink, s, capacity, rev_edge, G);
        }
 
        if(done || sums != m){cout<<"no\n"; continue;}
 
        // Calculate flow
        long flow = push_relabel_max_flow(G, source, sink);
        if(flow == m)
            cout << "yes\n";
        else
            cout << "no\n";
    }
 
    return 0;
}
