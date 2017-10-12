#include<iostream>
#include<cassert>
#include<CGAL/basic.h>
#include<CGAL/QP_models.h>
#include<CGAL/QP_functions.h>
using namespace std;
// choose exact integral type
#ifdef CGAL_USE_GMP
#include<CGAL/Gmpzf.h>
typedef CGAL::Gmpzf ET;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif
// program and solution types
typedef CGAL::Quadratic_program<int> Program;/////
typedef CGAL::Quadratic_program_solution<ET> Solution;


double ceil_to_double(const CGAL::Quotient<CGAL::Gmpzf> & x){
	double a = ceil(CGAL::to_double(x));
	while(a<x) a+=1;
	while(a-1 >= x) a-=1;
	return a;
}

double floor_to_double(const CGAL::Quotient<CGAL::Gmpzf> & x){
	double a = floor(CGAL::to_double(x));
	while(a>x) a-=1;
	while(a+1 <= x) a+=1;
	return a;
}

int main(){
	int p; cin>>p;
	while(p !=0){
		int a,b; cin>>a>>b;
		if(p==1){
			Program lp(CGAL::SMALLER, true, 0, false, 0);
			lp.set_a(0, 0, 1);
			lp.set_a(1, 0, 1);
			lp.set_b(0, 4);

			lp.set_a(0, 1 ,4);
			lp.set_a(1, 1, 2);
			lp.set_b(1, a*b);

			lp.set_a(0, 2, -1);
			lp.set_a(1, 2, 1);
			lp.set_b(2, 1);

			lp.set_d(0, 0,2*a);
			lp.set_c(1, -b);

			Solution s = CGAL::solve_quadratic_program(lp, ET());

			if(s.is_optimal() && s.objective_value() <= 0)////
				cout << (long)floor_to_double(-s.objective_value()) << endl;
			else if(s.is_unbounded())
				cout << "unbounded\n";
			else
				cout << "no\n";
		}
		else{
			Program lp(CGAL::LARGER, false, 0, true, 0);
			lp.set_a(0, 0, 1);
			lp.set_a(1, 0, 1);
			lp.set_b(0, -4);

			lp.set_a(0, 1 ,4);
			lp.set_a(1, 1 ,2);
			lp.set_a(2, 1 ,1);
			lp.set_b(1, -a*b);

			lp.set_a(0, 2 ,-1);
			lp.set_a(1, 2 ,1);
			lp.set_b(2, -1);

			lp.set_d(0,0, 2*a);
			lp.set_c(1, b);
			lp.set_d(2,2,  2);//// multiply by 2

			lp.set_l(2, true, 0);
			lp.set_u(2, false, 0);///
			Solution s = CGAL::solve_quadratic_program(lp, ET());

			if(s.is_optimal())
				cout <<(long) ceil_to_double(s.objective_value()) << endl;
			else if(s.is_unbounded())
				cout <<"unbounded\n";
			else
				cout <<"no\n";

		}
	cin >> p;

	}
	return 0;

}

