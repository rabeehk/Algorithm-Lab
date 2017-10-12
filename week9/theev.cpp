#include<iostream>
#include<CGAL/Exact_predicates_exact_constructions_kernel.h>
#include<CGAL/Min_circle_2.h>
#include<CGAL/Min_circle_2_traits_2.h>
#include<limits>
#include<algorithm>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef K::Point_2 P;

double ceil_to_double(const K::FT & x){
	double a =ceil(CGAL::to_double(x));
	while(a < x) a+=1;
	while(a-1>=x) a-=1;
	return a;
}

#define cerr if(false) cout
int main()
{

	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int n; cin>>n;
		vector<pair<K::FT,P> >ps;
		int x,y; cin>>x>>y;
		ps.push_back(make_pair(0, P(x, y)));
		for(int i=1; i<n; ++i){
			int x,y; cin>>x>>y;
			K::FT d = CGAL::squared_distance(P(x,y), ps[0].second);
			ps.push_back(make_pair(d, P(x,y)));
		}

		if(n <= 2) {cout << 0 << "\n"; continue; }

		//sort points based on distance from the first one
		sort(ps.begin(), ps.end());

		// make only one min circle
		Min_circle mc;
		K::FT minr2 = numeric_limits<double>::max();
		for(int i=n-1; i>0; i--){
			mc.insert(ps[i].second);
			K::FT r12 = mc.circle().squared_radius();
			K::FT r22 = ps[i-1].first;
			K::FT r2 = max(r22, r12); // take the maximum
			minr2 = min(minr2, r2);
			if(r12 > r22)
				break;
		}

		cout << (long)ceil_to_double(minr2) << "\n";
	}
	return 0;
}

