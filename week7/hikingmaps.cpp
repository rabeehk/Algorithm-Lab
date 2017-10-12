#include<iostream>
#include<vector>
#include<algorithm>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

struct triangle{
	vector<P> pts;
	void sort(){
		for(int i=0; i<6; i+=2){
			if(!CGAL::left_turn(pts[i], pts[i+1], pts[(i+2)%6]))
				swap(pts[i], pts[i+1]);
		}
	}
	bool contain(P p1, P p2){ ///// collinear 
		for(int i=0; i<6; i+=2){
			if(!(CGAL::left_turn(pts[i], pts[i+1], p1) ||
			   CGAL::collinear(pts[i], pts[i+1], p1)) )
				return false;
	
			if(!(CGAL::left_turn(pts[i], pts[i+1], p2) ||
			   CGAL::collinear(pts[i], pts[i+1], p2)) )
				return false;
		}
		return true;
	}
};
int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int m,n; cin >>m>>n;

		vector<P> ps;
		for(int i=0; i<m; ++i){
			long x,y; cin>>x>>y;
			ps.push_back(P(x,y));
		}

		vector<triangle>trs(n);
		for(int i=0; i<n; ++i){
			for(int j=0; j<6; ++j){
				long x,y; cin>> x>>y;
				trs[i].pts.push_back(P(x,y));
			}
			//sort triangle
			trs[i].sort();
		}

		vector<vector<bool> > cover(n); 
		for(int i=0; i<n; ++i){
			cover[i].resize(m-1);
			for(int j=0; j<(m-1); ++j)
				cover[i][j]= false;
		}
		
		for(int i=0; i<n; ++i){
			for(int j=0; j<(m-1); ++j){
				if (trs[i].contain(ps[j], ps[j+1]))
					cover[i][j] = true;
			}
		}


		////
		// find the minimum range(a,b)
		int mincost = numeric_limits<int>::max();
		int sum = 0;
		int b = 0; // end of the range
		vector<int> visited(m-1, 0);
		for(int i=0; i<n; ++i){
			for(int j=0; j<(m-1); ++j)
				if(cover[i][j]){
					if(visited[j]==0)
						sum++;
					visited[j]++;
				}

			//shrink the range
			while(sum == (m-1)){
				int cost = i-b+1;
				mincost = min(mincost,cost);

				for(int j=0; j<(m-1); ++j){
					if(cover[b][j])
						visited[j]--;
					if(visited[j] == 0)
						sum--;
				}
				b++;
			}
		}
		cout << mincost << "\n";
	}
	return 0;
}

