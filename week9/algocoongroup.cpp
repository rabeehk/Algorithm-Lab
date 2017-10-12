#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/push_relabel_max_flow.hpp>
#include<boost/tuple/tuple.hpp>
using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
		property<edge_capacity_t,
		long,
		property<edge_residual_capacity_t,
		long,
		property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;
typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_iterator EdgeIterator;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIterator;

void
addEdge( int from,int to, long c,
		EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge, Graph &G) {
	Edge e, reverseE;
	tie(e, tuples::ignore) = add_edge(from, to, G);
	tie(reverseE, tuples::ignore) = add_edge(to, from, G);
	capacity[e] = c;
	capacity[reverseE]= 0;
	rev_edge[e] = reverseE;
	rev_edge[reverseE] = e;
}

int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n,m; cin>>n>>m;
		Graph g(4);
		EdgeCapacityMap capacity = get(edge_capacity, g);
		ReverseEdgeMap rev_edge = get(edge_reverse, g);
		ResidualCapacityMap res_capacity = get(edge_residual_capacity, g);

		for(int i=0; i <m; ++i){
			int a,b,c; cin>>a>>b>>c;
			addEdge(a, b, c, capacity, rev_edge, g);
		}

		int v = 0;
		int min_s, min_t;
		long flow = numeric_limits<long>::max();
		for(int i=1; i < n; ++i){

			long flow1 = push_relabel_max_flow(g, v, i);
			if(flow1 < flow){
				flow = flow1;
				min_s = v; min_t = i;
			}

			long flow2 = push_relabel_max_flow(g, i, v);
			if(flow2 < flow){
				flow = flow2;
				min_s = i; min_t=v;
			}
		}

		// run flow again
		flow  = push_relabel_max_flow(g, min_s, min_t);
		cout << flow << endl;

		vector<int>sol;
		queue<int> q;
		q.push(min_s);
		vector<bool> visit(n);
		visit[min_s] = true;
		sol.push_back(min_s);

		//res_capacity = capacity-flow
		// if it is positive then it means it is not saturated and they belong
		// to source node, but if it is saturated they are the edges from
		// source to sink
		
		OutEdgeIterator out_i, out_end;
		while(!q.empty()){
			int cur = q.front(); q.pop();
			for(tie(out_i, out_end)=out_edges(cur, g);
					out_i != out_end; ++out_i){
				int tag = target(*out_i, g);
				if(res_capacity[*out_i]> 0){
					if(!visit[tag]){
						q.push(tag);
						visit[tag]=true;
						sol.push_back(tag);}
				}
			}
		}


	cout << sol.size() << " ";
	for(int i=0; i <sol.size(); ++i)
		cout << sol[i] << " ";
	cout << endl;

}
return 0;
}

