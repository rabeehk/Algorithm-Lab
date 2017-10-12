#include<iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;

double ceil_to_double(const K::FT &x){
	double a = ceil(CGAL::to_double(x));
	while(a< x) a+=1;
	while(a-1>=x) a-=1;
	return a;
}

int main()
{
	int n; cin>>n;
	while(n!=0){
		vector<P> ps;
		for(int i=0; i<n; ++i){
			long x,y; cin>>x>>y; ps.push_back(P(x,y));}
		Triangulation t;
		t.insert(ps.begin(), ps.end());

		K::FT mind = numeric_limits<double>::max();
		for(Triangulation::Finite_edges_iterator it=t.finite_edges_begin();
			it != t.finite_edges_end(); ++it){
			K::FT d = t.segment(it).squared_length();
			mind = min(mind, d);
		}

		cout << ceil_to_double(sqrt(mind)*100/2) << endl;
		cin >> n;
	}
	return 0;
}

