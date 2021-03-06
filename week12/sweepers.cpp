#include<iostream>
using namespace std;

#include<vector>
#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/push_relabel_max_flow.hpp>
#include<boost/tuple/tuple.hpp>
#include<boost/graph/connected_components.hpp>

using namespace boost;

typedef  adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef  adjacency_list<vecS, vecS, directedS, no_property,
property<edge_capacity_t,
long,
property<edge_residual_capacity_t,
long,property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;
typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;


void addEdge(int from, int to, long c,
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
		 int n,m,s; cin>>n>>m>>s;
		 
		 Graph g(n+2);
		 int source = n; int sink = n+1;
		 EdgeCapacityMap capacity = get(edge_capacity, g);
		 ReverseEdgeMap rev_edge = get(edge_reverse, g);
		 ResidualCapacityMap res_capacity = get(edge_residual_capacity, g);
		 vector<int>degree(n, 0);
		 //sources
		 vector<int>sources;
		 for(int i=0; i <s; ++i){
		   int a; cin>>a;
		   addEdge(source,a, 1, capacity, rev_edge, g);
		   degree[a]++;
		   sources.push_back(a);
		 }
		 for(int i=0; i <s; ++i){
		   int a; cin>>a;
		   addEdge(a,sink, 1, capacity, rev_edge, g);
		   degree[a]++;
		 }
		 
		 for(int i=0; i<m; ++i){
		   int a,b; cin>>a>>b;
		   addEdge(a,b,1,capacity, rev_edge, g);
		   addEdge(b,a,1,capacity, rev_edge, g);
		   degree[a]++; degree[b]++;
		 }
		 
		 bool done = false;
		 for(int i=0; i<n; ++i)
		   if(degree[i] %2 ==1){
		     cout <<"no\n";  done =true;break;}
		     if(done)
		       continue;
		     
		     //check for isolated edges
		     vector<int> comp(n+2);
		     connected_components(g, &comp[0]);
		     
		     //check every edge is within compoenents of source
		     vector<int> ss;
		     for(int i=0; i <s; ++i){
		       ss.push_back(comp[sources[i]]);
		     }
		     
		     for(int i=0; i <n; ++i){
		       if(degree[i] > 0){
			 if(find(ss.begin(), ss.end(), comp[i]) == ss.end()){
			   done=true; break;}
		       }
		     }
		     
		     if(done){ cout <<"no\n"; continue;}
		     
		     long flow = push_relabel_max_flow(g, source, sink);
		     if(flow != s){
		       cout <<"no\n";}
		       else
			 cout <<"yes\n";
		       
	       }
	       return 0;
	     }
	     
	     
	     
