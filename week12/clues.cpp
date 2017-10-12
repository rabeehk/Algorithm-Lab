// index: Deluanay, bipartiteness, coloring of nodes 
/*we build the graph with all edges smaller than R, there might be some missing
 , but we only care about the missing ones among the same colors*/
/**/
#include<iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>
#include<vector>
#include<cmath>
#include<algorithm>
#include<boost/graph/adjacency_list.hpp>
#include<CGAL/Triangulation_vertex_base_with_info_2.h>
#include <boost/graph/bipartite.hpp>
#include<boost/graph/connected_components.hpp>
#include<limits>
#include<queue>

using namespace boost;
using namespace std;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef K::Point_2 P;
typedef adjacency_list<vecS, vecS, undirectedS> Graph;
typedef graph_traits <Graph> traits;
typename traits::vertex_iterator vertex_iter, vertex_end;
typedef std::vector <int> partition_t;
typedef typename property_map <Graph, vertex_index_t>::type index_map_t;
typedef iterator_property_map <partition_t::iterator, index_map_t> partition_map_t;


bool bipartite(vector<vector<int> > &nb, int n, vector<P > (&pts)[2],
               vector<pair<P, int> > &ps){
  vector<bool> visited(n, false);
  vector<bool> color(n);
  bool f= true;
  for(int i=0; i <n; ++i){
   if(visited[i]) continue;
    std::queue<int> q;
    q.push(i);
    visited[i]=true;
    color[i] = false;
    pts[color[i]].push_back(ps[i].first);
    while(!q.empty()){
     int cur = q.front(); q.pop();
     for(int j=0; j<nb[cur].size(); ++j){
      int a = nb[cur][j];
      if(visited[a]){
	if(color[a] == color[cur])
	return false;
      }
      else{
	color[a]=!color[cur];
	pts[color[a]].push_back(ps[a].first);
        q.push(nb[cur][j]);
	visited[a]=true;
      }
      }
    }
  }
  return true;
}


/*if you check bipartiteness on the edges of Deluanay then it is wrong*/
int main()
{
    int T; cin>>T;
    for(int tt=0; tt<T; ++tt){
      double n,m,r; cin >> n >>m >>r;
      vector<pair<P, int> > ss;
      for(int i=0; i <n; ++i){
	long x,y; cin>>x>>y;
	ss.push_back(make_pair(P(x,y), i));
      }
      
      vector<P>as; vector<P>bs;
      for(int i=0; i <m; ++i){
	int x,y; cin>>x>>y;
	as.push_back(P(x,y));
	int x1,y1; cin>>x1>>y1;
	bs.push_back(P(x1,y1));
      }
      
      double r2=r*r;
      // I am sure that Deluanay has the closest station, so connections will be correct
      Triangulation t; t.insert(ss.begin(), ss.end());
      Graph g(n);
      vector<vector<int> > nb(n);
      for(Triangulation::Finite_edges_iterator it=t.finite_edges_begin();
	it != t.finite_edges_end(); ++it){
	if(CGAL::to_double(t.segment(it).squared_length()) <= r2){
	 Triangulation::Vertex_handle p1 = it->first->vertex(Triangulation::ccw(it->second));
	 Triangulation::Vertex_handle p2 = it->first->vertex(Triangulation::cw(it->second));
	 int a = p1->info();
	 int b = p2->info();
	 add_edge(a,b,g);
	 nb[a].push_back(b); nb[b].push_back(a);
	}
      }
     
   /*  Graph g(n);
     for(int i=0; i <n; ++i)
       for(int j=i+1; j <n; ++j){
	double d = squared_distance(ss[i].first, ss[j].first);
	if(d <= r2){
	  int a = ss[i].second; int b= ss[j].second;
	  add_edge(a,b,g);
	}
       }
     */
     
     partition_t partition (num_vertices (g));
     partition_map_t partition_map (partition.begin (), get (vertex_index, g));
     bool f = is_bipartite (g, get (vertex_index, g), partition_map);
     vector<P> pts[2];
     int count= -1;
     for (boost::tie (vertex_iter, vertex_end) = vertices (g); vertex_iter != vertex_end; ++vertex_iter)
     {
       count++;
       if(get (partition_map, *vertex_iter) == color_traits <int>::white ())
	 pts[0].push_back(ss[count].first);
       else
	 pts[1].push_back(ss[count].first);
    }
   
   //method 2
     /*vector<P>pts[2];
     bool f = bipartite(nb, n, pts, ss);*/
     
    Triangulation tcolor[2];
    double minE  = numeric_limits<double>::max();
    for(int i=0; i<2; ++i){
     tcolor[i].insert(pts[i].begin(), pts[i].end());
     //find min edge
     for(Triangulation::Finite_edges_iterator it= tcolor[i].finite_edges_begin();
	 it !=  tcolor[i].finite_edges_end(); ++it){
       minE = min(minE, CGAL::to_double( tcolor[i].segment(it).squared_length()));
       }
    }
    
    if(minE <= r2)
      f= 0;
     if(f==0){
       for(int i=0; i<m; ++i)
       cout<< "n"; 
       cout << endl; continue;
     }
              
     vector<int> comp(n);	 
     int num = connected_components(g, &comp[0]);	    
     for(int i=0; i<m; ++i){
       // distance
       double d12 = squared_distance(as[i], bs[i]);
       if(d12<=r2){cout <<"y"; continue;}
       
       Triangulation::Vertex_handle h1= t.nearest_vertex(as[i]);
       Triangulation::Vertex_handle h2= t.nearest_vertex(bs[i]);
       if(squared_distance(h1->point(), as[i]) > r2 || 
	  squared_distance(h2->point(), bs[i]) > r2  ){cout<<"n"; continue;}
	  
       int h1ind = h1->info(); int h2ind = h2->info();
       if(comp[h1ind] == comp[h2ind])
	 cout<<"y";
       else
	 cout<<"n";
     }
     cout << endl;
      
    }
    return 0;  
}