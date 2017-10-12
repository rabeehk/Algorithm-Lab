#include<iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>
#include<vector>
#include<limits>
#include<cmath>

using namespace std;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;

double floor_to_double(const K::FT &x){
  double a = std::floor(CGAL::to_double(x));
  while(a>x) a-=1;
  while(a+1<=x) a+=1;
  return a;
}

int main()
{
  int T; cin>>T;
  for(int tt=0; tt<T; ++tt){
    int n; cin>>n;
    vector<P> pts;
    for(int i=0; i <n; ++i){
     int x,y; cin>>x>>y; 
     pts.push_back(P(x,y));
    }
    Triangulation t; t.insert(pts.begin(), pts.end());
    
    K::FT mind = numeric_limits<K::FT>::max();
    for(Triangulation::Finite_edges_iterator it=t.finite_edges_begin(); 
	it!=t.finite_edges_end(); ++it){
	  K::Segment_2 s = t.segment(it);
	  mind = min(mind, sqrt(s.squared_length()));
    }
    
    cout << (long)floor_to_double(mind/2) << endl;
    
  }
  return 0;  
}