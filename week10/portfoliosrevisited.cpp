#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
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

vector<int> cs(42);
vector<int> rs(42);

#define cerr if(false)cout
int main()
{
	int n,m; cin>>n>>m;
	while( n!=0 && m!=0){
		Program lp(CGAL::SMALLER, true, 0, false, 0);
		int maxr = numeric_limits<int>::max();
		for(int i=0; i <n; ++i){
			cin >> cs[i] >> rs[i];
			//maxr=max(maxr, rs[i]);
		}
		for(int i=0; i <n; ++i)
			for(int j=0; j<n; ++j){
				int vij; cin>>vij;
				lp.set_d(i, j, 2*vij);
			}

		for(int i=0; i <n; ++i){
			lp.set_a(i, 0, cs[i]);
			lp.set_a(i, 1, rs[i]);
		}
		
	
		for(int p=0; p<m; ++p){
			int C, V; cin>>C>>V;
			lp.set_b(0, C);
			lp.set_r(1, CGAL::LARGER);
			int l=0; int h = numeric_limits<int>::max(); // you can put it to maxr but it does not change the time at all
			while(l<h){
				int r = l+((h-l)>>2);
				lp.set_b(1, r);
				Solution s = CGAL::solve_quadratic_program(lp, ET()); 
				
				if(!s.is_infeasible() && s.objective_value() <= V){
					l=r+1; 
				}
				else
					h = r;
			}
			cout << l-1 << endl;
		}
		cin >> n >>m;
	}
	return 0;
}

			
