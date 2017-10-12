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

int main()
{

	int n, m; cin>>n>>m;
	while(n!=0 && m!= 0){
		Program lp(CGAL::SMALLER, true, 0, false, 0);
		for(int i=0; i<n; ++i){
			int c,r; cin>>c >>r;
			lp.set_a(i, 0, c);
			lp.set_a(i,1, r);
		}
		lp.set_r(1, CGAL::LARGER);

		for(int i=0; i<n; ++i)
			for(int j=0; j<n; ++j){
				int a; cin >> a;
				lp.set_d(i, j, 2*a);
			}

		for(int i=0; i<m; ++i){
			int C, R, V; cin>>C>>R>>V;
			lp.set_b(0, C); lp.set_b(1, R);

			Solution s = CGAL::solve_quadratic_program(lp, ET());
			if(!s.is_infeasible() && s.objective_value() <= V)
				cout << "Yes.\n";
			else
				cout << "No.\n";

		}
		cin>>n>>m;
	}
	return 0;
}

