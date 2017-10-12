#include<iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>
#include<vector>
#include<limits>
#include<algorithm>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;

double ceil_to_double(const K::FT &x){
	double a = ceil(CGAL::to_double(x));
	while(a<x) a+=1;
	while(a-1 >= x) a-=1;
	return a;
}

int main()
{
	int n; cin>>n;
	while(n!=0){
		long ll,bb,rr,tt; cin>>ll>>bb>>rr>>tt;
		vector<P> pts;
		for(int i=0; i <n; ++i){
			long x,y; cin>>x>>y;
			pts.push_back(P(x,y));
		}
		Triangulation t; t.insert(pts.begin(), pts.end());
		// find the time for each bacteria
		vector<double> ts;
		for(Triangulation::Finite_vertices_iterator it=t.finite_vertices_begin();
			it != t.finite_vertices_end(); ++it){

			K::FT mind =numeric_limits<double>::max();
			Triangulation::Edge_circulator c= t.incident_edges(it);
			if(c!=0){
				do{
					if(!t.is_infinite(c)){//I want only finite edges here
						K::FT d = sqrt(t.segment(c).squared_length());
						d /= 2.0;
						mind = min(mind, d);
					}
				}while(++c != t.incident_edges(it));
			}

			//boundaries
			double x = it->point().x(); double y = it->point().y();
			double d1 = min( fabs(x-ll), fabs(x-rr));
			mind = min(mind, d1);
			d1 = min( fabs(y-tt), fabs(y-bb));
			mind = min(mind, d1);

			double time  = 0;
			if(mind <= 0.5)
				time =0;
			else
				time = ceil_to_double(sqrt(mind-0.5));

			ts.push_back(time);
		}

		sort(ts.begin(), ts.end());
		cout << ts[0] << " " << ts[n/2] << " " << ts[n-1] << "\n";
		cin >>n;
	}
	return 0;
}

