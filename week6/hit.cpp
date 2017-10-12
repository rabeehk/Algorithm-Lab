#include<iostream>
using namespace std;
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

int main()
{
	int n; cin>>n;
	while(n!=0){
		long a,b,c,d; cin>>a>>b>>c>>d;
		K::Ray_2 ray(P(a,b), P(c,d));

		bool f = false;
		for(int i=0; i <n; ++i){
			long s,r,t,u; cin>>s>>r>>t>>u;
			K::Segment_2 S(P(s,r), P(t,u));
			if(!f && CGAL::do_intersect(ray, S))
				f = true;
		}
		if(f)
			cout << "yes\n";
		else
			cout << "no\n";

		cin >> n;
	}
	return 0;
}

