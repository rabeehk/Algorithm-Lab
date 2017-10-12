#include<iostream>
#include<CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include<CGAL/Min_circle_2.h>
#include<CGAL/Min_circle_2_traits_2.h>
#include<vector>
#include<limits>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef K::Point_2 P;

double ceil_to_double(const K::FT &x){
	double a = ceil(CGAL::to_double(x));
	while(a < x) a+=1;
	while(a-1>=x) a-=1;
	return a;
}

int main()
{
	int n; cin>>n;
	while(n !=0 ){
		vector<P> ps;
		for(int i=0; i<n; ++i){
			long x,y; cin>>x>>y;
			ps.push_back(P(x,y));
		}
		Min_circle mc(ps.begin(), ps.end(), true);

		//boundary points
		vector<int> bnd;
		int count = 0;
		for(int i=0; i <n; ++i){
			if(mc.has_on_boundary(ps[i])){
				bnd.push_back(i);
				count++;
			}
		}
		if(count >= 4)
			cout << (long)ceil_to_double(sqrt(mc.circle().squared_radius())) << "\n";

		else{
			K::FT minr= numeric_limits<double>::max();
			for(int i=0; i < bnd.size(); ++i){
				swap(ps[bnd[i]], ps[n-1]);
				Min_circle mc1(&ps[0], &ps[n-1], true);
				K::FT r = mc1.circle().squared_radius();
				minr = min(minr, r);
				swap(ps[bnd[i]], ps[n-1]);
			}
			cout << (long)ceil_to_double(sqrt(minr)) << "\n";
		}
		cin >>n;
	}
	return 0;
}

