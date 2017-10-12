#include<iostream>
#include<vector>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<cmath>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 P3;

#include<CGAL/basic.h>
#include<CGAL/QP_models.h>
#include<CGAL/QP_functions.h>
// choose exact integral type
#ifdef CGAL_USE_GMP
#include<CGAL/Gmpzf.h>
typedef CGAL::Gmpzf ET;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif
// program and solution types
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;



vector<P3> ts(51);
vector<P3> hs(51);

bool solve(int d, int h, int t){
	Program lp(CGAL::SMALLER, false, 0, false, 0);
	for(int i=0; i <h; ++i){
		int num = 0;
		for(int j = 0; j<=d; j += 1){
			const double t1 = pow(hs[i].x(), j);
			for(int k= 0; k <= (d-j); k += 1){
				const double t2 = pow(hs[i].y(),k);
				for(int z=0; z<=d-(k+j); z+=1){
					lp.set_a(num,i, t1*t2*pow(hs[i].z(),z));
					num++;
				}
			}
		}
		lp.set_b(i, 1); lp.set_r(i, CGAL::LARGER);
	}


	for(int i=0; i <t; ++i){
		int num = 0;
		for(int j = 0; j<=d; j += 1){
			const double t1 =  pow(ts[i].x(), j);
			for(int k= 0; k <= (d-j); k += 1){
				const double t2 = pow(ts[i].y(),k);
				for(int z=0; z<=d-(k+j); z+=1){
					lp.set_a(num,i+h,t1*t2*pow(ts[i].z(),z));
					num++;
				}
			}
		}
		lp.set_b(i+h, -1);
	}


	CGAL::Quadratic_program_options options;
	options.set_pricing_strategy(CGAL::QP_BLAND);
	Solution s = CGAL::solve_linear_program(lp, ET(), options);
	if(s.is_infeasible())
		return false;
	else
		return true;
}
#define cerr if(false) cout

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		int nh, nt; cin>>nh>>nt;

		for(int i=0; i<nh; ++i){
			int x,y,z; cin>>x>>y>>z;
			hs[i]=P3(x,y,z);
		}

		for(int i=0; i<nt; ++i){
			int x,y,z; cin>>x>>y>>z;
			ts[i]=P3(x,y,z);
		}

		if(nt == 0 || nh == 0 )
			{cout << 0 << endl; continue;}



		//exponential search on degree
		int l=1;
		int h = 30;
		int d = 1;
		while( d<= 30){
			if(solve(d, nh, nt)){
				h=d;
				break;
			}
			else{
				l=d+1;
				d *=2; // do not multiply by more as
				 // when degree higher wrost to solve
			}
		}
		if(l == h)
			{cout << l << endl; continue;}
		
		while(l  < h){
			int d = l + (h-l)/2;
			if(solve(d, nh, nt)){ h=d;}
			else l = d+1;
		}

		// if the h and l has only one step different we need this
		if(!solve(l, nh, nt)) cout << "Impossible!\n";
		else cout << l << endl;

	}
	return 0;

}

