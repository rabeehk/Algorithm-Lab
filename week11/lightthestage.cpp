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
		
		vector<bool> alive1(m, true);
		vector<vector<int> > lp(n);
		for(int i=0; i<n; ++i){ //lamps
			for(int j=0; j<m; ++j){
				if(!alive1[j]) continue;
				double d=CGAL::to_double(CGAL::squared_distance(ls[i], ps[j]));
				if(d >= (rs[j]+h)*(rs[j]+h))
					lp[i].push_back(j);
				else
					alive1[j]=false;
			}
		}
	
		for(int i=n-1; i>=0 ; --i){
			if(lp[i].size() != 0){
				for(int j=0; j<lp[i].size(); ++j)
					cout << lp[i][j] << " ";
				cout << endl;
				break;
			}
		}
	}
	return 0;
}

