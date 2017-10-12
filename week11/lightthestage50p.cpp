#include<iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>
#include<vector>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;

int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int m,n; cin>>m>>n; //participants, lamps

		vector<P> ps;
		vector<long>rs(m);
		for(int i=0; i<m; ++i){
			long x,y; cin>>x>>y>>rs[i];
			ps.push_back(P(x,y));
		}
		int h; cin>>h;
		vector<P>ls;
		for(int i=0; i<n; ++i){
			long x,y; cin>>x>>y;
			ls.push_back(P(x,y));
		}

		// first find the participant alive after all lamps
		Triangulation t; t.insert(ls.begin(),ls.end());
		vector<int>alive;
		for(int i=0; i<m; ++i){
			P nearest = t.nearest_vertex(ps[i])->point();
			double d=CGAL::to_double(CGAL::squared_distance(nearest, ps[i]));
			if(d >= (rs[i]+h)*(rs[i]+h))
				alive.push_back(i);
		}
		if(alive.size() != 0){
			for(int i=0; i<alive.size(); ++i)
				cout << alive[i] << " ";
			cout << endl;
			continue;
		}
	}
	return 0;
}

