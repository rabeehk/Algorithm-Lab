#include<iostream>
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

double floor_to_double(const CGAL::Quotient<CGAL::Gmpzf> & x)
{
	double a = floor(CGAL::to_double(x));
	while(a > x) a-=1;
	while(a+1 <= x) a+=1;
	return a;
}

int main()
{

	int n, m; cin>>n>>m;
	while(n!=0 && m!= 0){
		Program lp(CGAL::SMALLER, true, 0, false, 0);
		for(int i=0; i<n; ++i){
			int minf, maxf; cin>>minf >> maxf;
			lp.set_b(i, minf); lp.set_r(i, CGAL::LARGER);
			lp.set_b(i+n, maxf);
		}
		for(int i=0; i<m; ++i){
			int p; cin>>p;
			lp.set_c(i, p);
			for(int j=0; j<n; ++j){
				int c; cin>>c;
				lp.set_a(i,j,c);
				lp.set_a(i,j+n,c);
			}
		}

		Solution s = CGAL::solve_linear_program(lp, ET());
		if(s.is_optimal())
			cout << floor_to_double(s.objective_value()) << "\n";
		else
			cout << "No such diet.\n";

	cin>>n>>m;
	}
	return 0;
}

