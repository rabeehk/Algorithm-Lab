#include<iostream>
#include<CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include<CGAL/Min_circle_2.h>
#include<CGAL/Min_circle_2_traits_2.h>
#include<vector>
#include<cmath>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef K::Point_2 P;

double ceil_to_double_sqrt(const K::FT &x)
{
	/* wrong: double a = ceil(sqrt(CGAL::to_double(x)));
	while(a*a < x ) a+= 1;
	while((a-1)*(a-1) >= x) a-=1;
	return a;*/
	double a = ceil(CGAL::to_double(x));
	while(a < x ) a+= 1;
	while(a-1 >= x) a-=1;
	return a;

}

int main(){
	int n; cin>>n;
	while(n!=0){
		vector<P> ps;
		for(int i=0; i <n; ++i){
			long x,y; cin>>x>>y;
			ps.push_back(P(x,y));
		}
		Min_circle mc(ps.begin(), ps.end(), true);
		//wrong: cout << (long)ceil_to_double_sqrt(mc.circle().squared_radius()) << "\n";
		cout << (long)ceil_to_double_sqrt(sqrt(mc.circle().squared_radius())) << "\n";
		cin >>n;
	}
	return 0;
}

