#include<iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;


int main()
{
	int n; cin>>n;
	while(n!=0){
		vector<P> ps;
		for(int i=0; i<n; ++i){
			long x,y; cin>>x>>y; ps.push_back(P(x,y));}
		Triangulation t;
		t.insert(ps.begin(), ps.end());

		int m; cin>>m;
		vector<P> ls;
		for(int i=0; i<m; ++i){
			int x,y; cin>>x>>y; ls.push_back(P(x,y));
		}

		for(int i=0; i <m; ++i){
			P p = t.nearest_vertex(ls[i])->point();
			double d = CGAL::to_double(CGAL::squared_distance(p, ls[i]));
			cout << (long)d << "\n";
		}
		cin >> n;
	}
	return 0;
}

