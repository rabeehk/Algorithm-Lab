#include<iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>
#include<queue>
#include<vector>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;
typedef Triangulation::Face_handle F;
int main()
{
	ios_base::sync_with_stdio(false);
	int n; cin>>n;
	while(n!=0){
		vector<P> pts;
		for(int i=0; i<n; ++i){
			int x,y; cin>>x>>y;
			pts.push_back(P(x,y));
		}
		Triangulation t; t.insert(pts.begin(), pts.end());

		int m; cin>>m;
		for(int i=0; i<m; ++i){
			int x,y; double d;  cin>>x>>y>>d;
			P user = P(x,y);
			P near = t.nearest_vertex(user)->point();
			double r = CGAL::to_double(CGAL::squared_distance(near, user));
			if( r < d){cout <<"n"; continue;}
			F face= t.locate(user);
			queue<F> q;
			map<F, bool> visited;
			q.push(face);
			visited[face]=true;
			bool done = false;
			while(!q.empty()){
				F cur = q.front(); q.pop();
				visited[cur] =true;
				if(t.is_infinite(cur)){
					done =true;
					break;
				}
				for(int i=0; i<3; ++i){
					F nb = cur->neighbor(i);
					if(visited.find(nb) == visited.end()){
						if(t.segment(cur, i).squared_length()
								>= 4*d){
							q.push(nb);
							visited[nb]=true;
						}
					}

				}
			}
			if(done)
				cout<<"y";
			else
				cout <<"n";

		}
		cout << endl;
		cin >>n;
	}
	return 0;
}

