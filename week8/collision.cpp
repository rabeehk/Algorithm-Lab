//============================================================================
// Name        : man.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <vector>
#include <iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include<limits>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;
int main() {
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n; cin>>n;
		int d; cin>>d;
		vector<P>ps;
		for(int i=0; i<n; ++i){
			int x,y; cin>>x>>y;
			ps.push_back(P(x,y));
		}
		Triangulation t; t.insert(ps.begin(),ps.end());
		int count =0;
		for(Triangulation::Finite_vertices_iterator it = t.finite_vertices_begin();
				it != t.finite_vertices_end(); ++it){
			double mind = numeric_limits<double>::max();
			Triangulation::Edge_circulator c = t.incident_edges(it);
			if(c!=0){
				do{
					if(!t.is_infinite(c)){
						double r = sqrt(t.segment(c).squared_length());
						mind = min(r, mind);
					}
				}while(++c != t.incident_edges(it));
			}

			if(mind < d)
				count++;
		}
		cout << count << "\n";
	}
	return 0;
}

