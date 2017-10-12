/*
 first observation is that edges of traingulation are the most constraint,
 we do not need to test for all pairwise distances, as if they stasfies 
 triangulation edges they satisfy all.
 */

#include<iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>
#include<CGAL/Triangulation_vertex_base_with_info_2.h>
#include<vector>
#include<cmath>
#include<algorithm>

#include<cassert>
#include<CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
// choose exact integral type
#ifdef CGAL_USE_GMP
#include <CGAL/Gmpzf.h>
typedef CGAL::Gmpzf ET;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif
// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef K::Point_2 P;

double ceil_to_double(const CGAL::Quotient<CGAL::Gmpzf> & x)
{
    double a = std::ceil(CGAL::to_double(x));
    while(a<x) a+=1; while(a-1>=x) a-=1;
    return a;  
}


double floor_to_double(const CGAL::Quotient<CGAL::Gmpzf> & x)
{
  double a = std::floor(CGAL::to_double(x));
  while(a>x) a-=1; while(a+1<=x) a+=1;
  return a;  
}




//note in this question: their suggested lower bound is
//to make the minimum between all pairs, and use it

int main()
{
  int T; cin>>T;
  for(int tt=0; tt<T; ++tt){
    Program lp(CGAL::SMALLER, false, 0, false, 0);
    int n; cin>>n;
    
    vector<pair<P, int> > pts;
    for(int i=0; i <n; ++i){
	int x,y; cin>>x>>y;
	pts.push_back(make_pair(P(x,y), i));
    }  
    Triangulation t; t.insert(pts.begin(), pts.end());
    
    //set the minimum bounds
    K::FT minD = numeric_limits<K::FT>::max();
    for(int i=0; i <n; ++i){
      K::FT d= CGAL::squared_distance(t.nearest_vertex(pts[i].first)->point(), pts[i].first); //.first
      lp.set_c(i, -1);
      minD= min(minD, d);
    }
   
    for(int i=0; i <n; ++i){ 
    	lp.set_l(i, sqrt(CGAL::to_double(minD))/2);
    }
	
    long pre = (long)floor_to_double(sqrt(CGAL::to_double(minD))/2);
    
    int num=0;
    for(Triangulation::Finite_edges_iterator it=t.finite_edges_begin(); it != t.finite_edges_end();
      it++){
      int ind1= it->first->vertex(Triangulation::ccw(it->second))->info();
      int ind2= it->first->vertex(Triangulation::cw(it->second))->info();
    
      double len = sqrt(CGAL::to_double(t.segment(it).squared_length()));
    
      lp.set_a(ind1, num, 1);
       lp.set_a(ind2, num,1 );
       lp.set_b(num, len);
     num++;
    }
    
    Solution s=CGAL::solve_linear_program(lp, ET());
    cout << (long)ceil_to_double(-s.objective_value())-pre << endl; // pre is long and ceil up does not make snese 
  }
  return 0;
}
