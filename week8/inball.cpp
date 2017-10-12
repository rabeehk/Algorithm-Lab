#include<iostream>
#include<cmath>
using namespace std;

#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
// choose exact integral type
#ifdef CGAL_USE_GMP
#include <CGAL/Gmpzf.h>
typedef CGAL::Gmpzf ET;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif
// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

double floor_to_double(const CGAL::Quotient<CGAL::Gmpzf> x){
	double a=floor(CGAL::to_double(x));
	while(a > x ) a-=1;
	while(a+1 <= x) a+=1;
	return a;
}

int main()
{
	int n, d; cin>>n;
	while(n!=0){
		cin >> d;
		Program lp(CGAL::SMALLER, false, 0, false, 0);
		for(int e=0; e<n; ++e){
			long norm=0;
			for(int i=0; i<d; ++i){
				int a; cin>>a;
				lp.set_a(i,e, a);
				norm += a*a;
			}
			norm = sqrt(norm);
			int b; cin>>b;
			lp.set_b(e, b);
			lp.set_a(d, e, norm);
		}

		lp.set_l(d, true, 0);
		lp.set_c(d, -1);
		Solution s = CGAL::solve_linear_program(lp, ET());
		if(s.is_unbounded())
			cout << "inf\n";
		else if(s.objective_value() <=0 && !s.is_infeasible())
			cout << (long)floor_to_double(-s.objective_value()) << "\n";
		else
			cout << "none\n";

		cin>>n;
	}
	return 0;
}

