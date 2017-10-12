#include<iostream>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

#include <CGAL/QP_models.h>
#include<CGAL/QP_functions.h>
// choose exact integral type
#ifdef CGAL_USE_GMP
#include<CGAL/Gmpzf.h>
typedef CGAL::Gmpzf ET;
#else
#include <CGAL/MP_Float.h>
typedef
CGAL::MP_Float ET;
#endif
// program and solution types
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef K::Segment_2 S;

int main()
{
	int T; cin>>T;
	for(int tt=0; tt<T; ++tt){
		Program lp(CGAL::SMALLER, true, 1, true, pow(2, 12));
		int l,s,w; cin>>l>>s>>w;
		vector<P> ls;
		for(int i=0; i<l; ++i){
			int x,y; cin>>x>>y;
			ls.push_back(P(x,y));
		}
		vector<P>ss;
		for(int i=0; i<s; ++i){
			int x,y,M; cin>>x>>y>>M;
			ss.push_back(P(x,y));
			lp.set_b(i, M);
			lp.set_r(i+s, CGAL::LARGER);
			lp.set_b(i+s, 1);
		}

		vector<S> ws;
		for(int i=0; i <w; ++i){
			int a,b,c,d; cin>>a>>b>>c>>d;
			ws.push_back(S(P(a,b), P(c,d)));
		}

		for(int i=0; i<s; ++i){ //stamp
			for(int j=0; j<l; ++j){
				bool flag = false;
				S sl = S(ss[i], ls[j]);
				/*for(int k=0; k<w; ++k){
					if(CGAL::do_intersect(sl,ws[k])){
						flag =true; break;
					}
				}
				if(!flag){*/
					double c = CGAL::to_double(CGAL::squared_distance(ss[i], ls[j]));
					lp.set_a(j, i, 1.0/c);
					lp.set_a(j, i+s, 1.0/c);
				//}
			}
		}

		Solution sol =CGAL::solve_linear_program(lp, ET());
		if(!sol.is_infeasible()){
			cout << "yes\n";
		}
		else
			cout << "no\n";
	}
	return 0;
}

